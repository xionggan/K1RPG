#pragma once
#include "Frame.h"

class Item;

class ItemObject : public Walkable
{
public:

	ItemObject(Item* item, Position* _position, int width = 1, int height = 1, int type = MT_ITEM);

	~ItemObject();

public:

	virtual void Update();

private:

	_SYSTEM_PRIVATE_(Item*,Item,item);

};

