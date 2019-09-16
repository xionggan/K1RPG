#include "Unity.h"

ItemFactory* ItemFactory::instance;

ItemFactory::ItemFactory()
{
	instance = nullptr;
}

ItemFactory::~ItemFactory()
{
}

ItemFactory* ItemFactory::GetInstance(){
	if (instance == nullptr){
		instance = new ItemFactory();
	}
	return instance;
}

Item* ItemFactory::CreateItem(ItemType itemType, int count){

	Item* item  = nullptr;

	switch (itemType)
	{
	case IT_DRILL:
		item = new Equipment(itemType,ET_WEAPON ,"钻头", 1, 0);
		item->SetThumbnail("∧");
		item->SetPrice(100);
		break;
	case IT_CANNON:
		item = new Equipment(itemType, ET_WEAPON, "加农炮", 10, 0);
		item->SetThumbnail("○");
		item->SetPrice(100);
		break;
	case IT_LASERGUN:
		item = new Equipment(itemType, ET_WEAPON,"激光炮", 10, 0);
		item->SetThumbnail("⊙");
		item->SetPrice(150);
		break;
	case IT_WALLBUILDER:
		item = new Equipment(itemType, ET_WEAPON, "造墙器", 0, 0);
		item->SetThumbnail("□");
		item->SetPrice(100);
		break;
	case IT_REACTIVEARMOR:
		item = new Equipment(itemType, ET_ARMOR, "反应装甲", 0, 5);
		item->SetThumbnail("※");
		item->SetPrice(100);
		break;
	case IT_HP:
		item = new HpMedinice(itemType, "汽油", count, 30);
		item->SetThumbnail("Φ");
		item->SetPrice(20);
		break;
	case IT_AMMO:
		item = new Consumables(itemType, "炮弹", count);
		item->SetThumbnail("●");
		item->SetPrice(10);
		break;
	case IT_STONE:
		item = new Consumables(itemType, "石材", count);
		item->SetThumbnail("◆");
		item->SetPrice(10);
		break;
	default:
		break;
	}

	return item;
}