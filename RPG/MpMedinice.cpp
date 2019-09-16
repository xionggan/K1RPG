#include "MpMedinice.h"
#include "Player.h"

MpMedinice::MpMedinice(int id, string _pFlag, int _count, int _recoverCount) :Medinice(id,_pFlag, _count, _recoverCount)
{
}

MpMedinice::~MpMedinice()
{
}

void MpMedinice::Effect(Player* hero){
	int curMp = hero->GetMp();
	int maxMp = hero->GetMaxMp();
	int recoverCount = GetRecoverCount();
	if (curMp + recoverCount < maxMp){
		hero->SetMp(curMp + recoverCount);
	}
	else{
		hero->SetMp(maxMp);
	}

	Consumables::Effect(hero);
}