#include "Unity.h"


Shop::Shop(string title, Position* _startPos)
:Window(title, _startPos , 18, 17)
{
	curIndex = 0;
	items = vector<Item*>();
}

Shop::~Shop()
{

}

void Shop::init(){

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_CANNON));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_LASERGUN));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_WALLBUILDER));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_REACTIVEARMOR));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_HP));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_AMMO, 10));

	items.push_back(ItemFactory::GetInstance()->CreateItem(ItemType::IT_STONE, 10));
}

void Shop::Display(){

	DrawBorder();

	int contentStartX = GetStartPos()->x + 1;

	int contentStartY = GetStartPos()->y + 1;

	int size = items.size();

	GotoXY(contentStartX * 2, contentStartY);

	printf("图标│详情                │价格");

	GotoXY(contentStartX * 2, contentStartY + 1);

	for (size_t j = 1; j < GetWidth() - 1; j++)
	{
		printf("--");
	}

	for (size_t i = 1; i <= size; i++)
	{
		Item* temp = items[i - 1];

		GotoXY(contentStartX * 2, contentStartY + i * 2);

		if (curIndex == i - 1){
			SetColor(14,6);
		}
		else{
			SetColor(14, 0);
		}
		
		printf("%-4s│%-20s│%-4d", temp->GetThumbnail().data(),temp->GetDescribe().data(),temp->GetPrice());

		GotoXY(contentStartX * 2, contentStartY + i * 2 + 1);

		SetColor(14, 0);

		for (size_t j = 1; j < GetWidth() - 1; j++)
		{
			printf("--");
		}
	}
}

void Shop::AcceptKbEvent(char key){
	switch (key)
	{
	case 'w':
		if (curIndex > 0){
			curIndex -= 1;
		}
		break;
	case 's':
		if (curIndex < items.size() - 1){
			curIndex += 1;
		}
		break;
	case 'j':
		{
			Player* player = dynamic_cast<Player*>(GetScene()->GetMainPlayer());
			BuyItem(player);
		}
		break;
	case 'l':
		UnBind();
		break;
	default:
		return;
	}
	Display();
}


void Shop::BuyItem(Player* player){
	Item* curItem = items[curIndex];

	Consumables* consumables = dynamic_cast<Consumables*>(curItem);

	int count = consumables == NULL ? 1 : consumables->GetCount();

	int price = curItem->GetPrice();
	if (player->GetCoin() >= price){
		player->SetCoin(player->GetCoin() - price);
		player->GetItemBag()->AddItem(ItemFactory::GetInstance()->CreateItem((ItemType)curItem->GetId(),count));
	}
}
