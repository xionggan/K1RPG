#pragma once
#include "Frame.h"
#include "Item.h"


class Consumables :public Item
{
public:
	Consumables(int id ,string _pFlag, int count);

	~Consumables();

	void SetCount(int count);

public:
	virtual void Effect(Player* hero);

private:
	_SYSTEM_PRIVATE_READONLY_(int, Count, count);
	_SYSTEM_PRIVATE_READONLY_(int, maxCount, maxCount);
};