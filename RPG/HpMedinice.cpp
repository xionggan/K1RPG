#include "Unity.h"

HpMedinice::HpMedinice(int id, string _pFlag, int _count, int _recoverCount) :Medinice(id,_pFlag, _count, _recoverCount)
{

	SetDescribe(GetFlag() + " »Ø¸´Á¿" + int2str(_recoverCount));
}

HpMedinice::~HpMedinice()
{
}

void HpMedinice::Effect(Player* hero){
	int curHp = hero->GetHp();
	int maxHp = hero->GetMaxHp();
	int recoverCount = GetRecoverCount();
	if (curHp + recoverCount < maxHp){
		hero->SetHp(curHp + recoverCount);
	}
	else{
		hero->SetHp(maxHp);
	}

	Consumables::Effect(hero);

}