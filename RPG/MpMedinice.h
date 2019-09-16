#pragma once
#include "Marco.h"
#include "Medinice.h"



class MpMedinice :public Medinice
{
public:
	MpMedinice(int id,string _pFlag, int _count, int _recoverCount);
	~MpMedinice();
	virtual void Effect(Player* hero);
private:

};