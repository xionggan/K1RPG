#include"Unity.h"

Consumables::Consumables(int id, string _pFlag, int _count) :Item(id, _pFlag)
{
	count = _count;
	maxCount = 99;
	string describe = GetFlag() + ",数量" + int2str(count);
	SetDescribe(describe);
}

Consumables::~Consumables(){

}

void Consumables::Effect(Player* hero){
	int count = GetCount();
	if (count > 1){
		SetCount(count - 1);
	}
	else if (count == 1){
		Bag* bag = hero->GetItemBag();
		bag->DropItem(bag->findItemPos(GetId()));
	}
}


void Consumables::SetCount(int count){
	this->count = count;
	string describe = GetFlag() + ",数量" + int2str(count);
	SetDescribe(describe);
}