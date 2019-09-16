#include "Medinice.h"


Medinice::Medinice(int id, string _pFlag, int _count, int _recoverCount) : Consumables(id,_pFlag, _count)
{
	recoverCount = _recoverCount;
}

Medinice::~Medinice()
{
}