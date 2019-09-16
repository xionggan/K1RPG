#pragma once
#include "Frame.h"
#include "Item.h"

class Equipment : public Item
{
public:

	Equipment(int id, int type ,string _pFlag, int atk, int def);

	~Equipment();

public:

	virtual void Effect(Player* hero);

	virtual void UnEffect(Player* hero);

private:
	_SYSTEM_PRIVATE_(int, Atk, atk);
	_SYSTEM_PRIVATE_(int, Def, def);
	_SYSTEM_PRIVATE_(int, Type, type);
	_SYSTEM_PRIVATE_(bool, IsEquiped, isEquiped);
};