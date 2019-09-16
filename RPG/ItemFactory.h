#pragma once

class ItemFactory
{
public:

	static ItemFactory* GetInstance();

	Item* CreateItem(ItemType itemType, int count = 1);

	~ItemFactory();

private:

	ItemFactory();

	static ItemFactory* instance;
};