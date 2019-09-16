#pragma once
#include "Marco.h"
#include "Consumables.h"

class Medinice :public Consumables
{
public:
	Medinice(int id, string _pFlag, int _count, int _recoverCount);
	~Medinice();
private:
	_SYSTEM_PRIVATE_(int, RecoverCount, recoverCount);
};