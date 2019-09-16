#include "Unity.h"


Bag::Bag(Player* owner, Position* startPos, int maxX, int maxY, bool showItemDescribe, string title)
:Window(title, startPos, maxX * 2 + 1, maxY * 2 + 1 + showItemDescribe * 2)
{
	this->maxX = maxX;
	this->maxY = maxY;
	this->showItemDescribe = showItemDescribe;
	this->owner = owner;
	curPos = Position(0,0);
	items = map<Position, Item*>();
}

Bag::~Bag()
{

}

map<Position, Item*>& Bag::GetItems(){
	return items;
}

void Bag::AddItem(Item* pItem){
	//判断叠加
	Consumables* addItem = dynamic_cast<Consumables*>(pItem);
	if (addItem != NULL){
		map<Position, Item*>::iterator begin = items.begin();
		while (begin != items.end()){
			Consumables* temp = dynamic_cast<Consumables*>((*begin).second);
			if (temp != NULL){
				if (temp->GetId() == addItem->GetId()){
					if (temp->GetCount() + addItem->GetCount() <= temp->GetmaxCount()){
						temp->SetCount(temp->GetCount() + addItem->GetCount());
						return;
					}
					else{
						int addCount = temp->GetmaxCount() - temp->GetCount();
						temp->SetCount(temp->GetCount() + addCount);
						addItem->SetCount(addItem->GetCount() - addCount);
					}
				}
			}
			begin++;
		}
	}

	Position tempPos = Position();
	for (int i = 0; i < maxY; i++){
		for (int j = 0; j < maxX; j++){
			tempPos.x = j;
			tempPos.y = i;
			if (items.find(tempPos) == items.end()){
				items[Position(j, i)] = pItem;
				return;
			}
		}
	}
	printf("背包已满,无法继续添加！");
}

void Bag::AddItem(Position pos, Item* item){
	items[pos] = item;
}

void Bag::DropItem(){
	if (items.find(curPos) != items.end()){
		items.erase(curPos);
	}
}

void Bag::DropItem(Position position){
	if (items.find(position) != items.end()){
		items.erase(position);
	}
}

void Bag::UseItem(Player* target){
	if (target == nullptr){
		target = owner;
	}
	if (items.find(curPos) != items.end()){
		items[curPos]->Effect(target);
	}
}

void Bag::UseItem(Position position, Player* target){
	if (target == nullptr){
		target = owner;
	}
	if (items.find(position) != items.end()){
		items[position]->Effect(target);
	}
}

Item* Bag::findItem(int id){
	map<Position, Item*>::iterator begin = items.begin();
	while (begin != items.end()){
		Item* temp = (*begin).second;
		if (temp->GetId() == id){
			return (*begin).second;
		}
		begin++;
	}
	return nullptr;
}

Position Bag::findItemPos(int id){
	map<Position, Item*>::iterator begin = items.begin();
	while (begin != items.end()){
		Item* temp = (*begin).second;
		if (temp->GetId() == id){
			return (*begin).first;
		}
		begin++;
	}
	return Position(-1, -1);
}

int Bag::findItemCount(int id){
	int count = 0;
	map<Position, Item*>::iterator begin = items.begin();
	while (begin != items.end()){
		Item* tempItem = (*begin).second;
		if (tempItem->GetId() == id){
			Consumables* tempConsumables = dynamic_cast<Consumables*>(tempItem);
			if (tempConsumables != NULL){
				count += tempConsumables->GetCount();
			}
			else{
				count++;
			}
		}
		begin++;
	}
	return count;
}

void  Bag::SetToShortCut(Bag* target){
	if (items.find(curPos) != items.end()){

		Item* tempItem = (*items.find(curPos)).second;

		for (size_t i = 0; i < target->GetMaxX(); i++)
		{
			Position tempPos = Position(i,0);
			auto targetTempIter = target->GetItems().find(tempPos);
			if (targetTempIter != target->GetItems().end()){
				Item* targetTemp = (*targetTempIter).second;
				if (targetTemp == tempItem){
					target->DropItem(tempPos);
					return;
				}
			}
		}

		target->AddItem(items[curPos]);
	}
}


//按获得顺序重新排序，消除中间空位
void Bag::Sort(){
	map<Position, Item*> tempData;
	tempData.swap(items);
	items.clear();
	auto begin = tempData.begin();
	while (begin != tempData.end()){
		AddItem((*begin).second);
		begin++;
	}
}

void Bag::Display(){
	DrawBorder();
	Position* startpos = GetStartPos();
	GotoXY((startpos->x + 1) * 2, startpos->y + 1);
	for (size_t i = 1; i < maxY * 2; i++)
	{
		for (size_t j = 1; j < maxX * 2; j++)
		{
			SetColor(GetBorderColor(), 0);
			if (i % 2 == 0){
				printf("--");
			}
			else{
				if (j % 2 == 0){
					printf("│");
				}
				else{
					if (i == curPos.y * 2 + 1 && j == curPos.x * 2 + 1){
						SetColor(GetBorderColor(), 8);
					}

					auto item = items.find(Position((j - 1) / 2, (i - 1) / 2));

					if (item != items.end()){

						Equipment* tempItem = dynamic_cast<Equipment*>((*item).second);

						if (tempItem != NULL && tempItem->GetIsEquiped()){
							SetColor(GetBorderColor(), 6);
						}

						printf("%s",(*item).second->GetThumbnail().data());
					}
					else{
						printf("  ");
					}
					SetColor(GetBorderColor(), 0);
				}
			}
		}
		GotoXY((GetStartPos()->x + 1) * 2, GetStartPos()->y + 1 + i);
	}

	if (showItemDescribe){

		GotoXY((startpos->x + 1) * 2, GetStartPos()->y + maxY * 2);

		for (size_t i = 1; i < maxX * 2; i++)
		{
			printf("--");
		}

		GotoXY((startpos->x + 1) * 2, GetStartPos()->y + maxY * 2 + 1);

		for (size_t j = 1; j < maxX * 2; j++){
			printf("  ");
		}

		GotoXY((startpos->x + 1) * 2, GetStartPos()->y + maxY * 2 + 1);

		map<Position, Item*>::iterator choosePos = items.find(curPos);

		if (choosePos != items.end()){
			printf("%s", (*choosePos).second->GetDescribe().data());
		}
	}
}


void Bag::AcceptKbEvent(char key){
	int x = curPos.x;
	int y = curPos.y;
	switch (key)
	{
	case 'w':
		if (y > 0){
			curPos.y = y - 1;
		}
		break;
	case 's':
		if (y < maxY - 1){
			curPos.y = y + 1;
		}
		break;
	case 'a':
		if (x > 0){
			curPos.x = x - 1;
		}
		break;
	case 'd':
		if (x < maxX - 1){
			curPos.x = x + 1;
		}
		break;
	case 'j':
		UseItem();
		break;
	case 'x':
		if (items.find(curPos) != items.end()){
			Equipment* curItem = dynamic_cast<Equipment*>((*(items.find(curPos))).second);
			if (curItem != NULL && curItem->GetType() == ET_WEAPON){
				SetToShortCut(owner->GetCutBag());
			}
			else{
				GotoXY(0, 35);
				//printf("只有武器才能设置到快捷栏!");
			}
		}
		break;
	case 'c':
		UnBind();
		break;
	default:
		break;
	}
	Display();
}