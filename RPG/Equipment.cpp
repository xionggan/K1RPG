#include "Unity.h"

Equipment::Equipment(int _id, int _type, string _pFlag, int _atk, int _def) :Item(_id, _pFlag)
{
	atk = _atk;
	def = _def;
	type = _type;
	isEquiped = false;

	string describe = "";
	if (atk >0){
		describe = describe + "¹¥»÷Á¦:" + int2str(GetAtk());
	}
	if (def > 0){
		describe = describe + "·ÀÓùÁ¦:" + int2str(GetDef());
	}
	SetDescribe(GetFlag() +  " " + describe);
}

Equipment::~Equipment()
{
}

void Equipment::Effect(Player* hero){

	if (isEquiped){
		return;
	}

	int curAtk = hero->GetAtk();
	int curDef = hero->GetDef();
	hero->SetAtk(curAtk + atk);
	hero->SetDef(curDef + def);
	isEquiped = true;

	switch (type)
	{
	case ET_WEAPON:
		if (hero->GetWeapon() != nullptr){
			hero->GetWeapon()->UnEffect(hero);
		}
		hero->SetWeapon(this);
		break;
	case ET_ARMOR:
		if (hero->GetArmor() != nullptr){
			hero->GetArmor()->UnEffect(hero);
		}
		hero->SetArmor(this);
		break;
	default:
		break;
	}

	hero->ChangePicture();

}

void Equipment::UnEffect(Player* hero){
	int curAtk = hero->GetAtk();
	int curDef = hero->GetDef();
	hero->SetAtk(curAtk - atk);
	hero->SetDef(curDef - def);
	isEquiped = false;
	switch (type)
	{
	case ET_WEAPON:
		hero->SetWeapon(nullptr);
		break;
	case ET_ARMOR:
		hero->SetArmor(nullptr);
		break;
	default:
		break;
	}
}