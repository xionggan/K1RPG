#pragma once
#include "Marco.h"
#include "Medinice.h"

class HpMedinice :public Medinice
{
public:
	HpMedinice(int id ,string _pFlag, int _count, int _recoverCount);
	~HpMedinice();
	virtual void Effect(Player* hero);
private:
};