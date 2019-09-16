#pragma once
#include "Frame.h"

class Player;

class Item
{
public:
	Item();
	Item(int id,string _pFlag);
	virtual ~Item();
	virtual void Effect(Player* player);
private:
	_SYSTEM_PRIVATE_(int, Id, id);
	_SYSTEM_PRIVATE_(string, Flag, pFlag);
	_SYSTEM_PRIVATE_(string, Describe,describe);
	_SYSTEM_PRIVATE_(string, Thumbnail, thumbnail);
	_SYSTEM_PRIVATE_(int, Price, price);
};