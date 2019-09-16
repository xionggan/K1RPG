#pragma once
#include<map>
#include "Marco.h"
#include "Position.h"
#include "GameLib.h"
#include "Window.h"
using namespace std;

class Item;

class Bag : public Window
{
public:

	Bag(Player* owner, Position* startPos, int maxX = 5, int maxY = 3, bool showItemDescribe = true, string title = "±³°ü");
	~Bag();
	void AddItem(Item* item);
	void AddItem(Position pos,Item* item);
	void DropItem();
	void DropItem(Position position);
	void UseItem(Player* target = nullptr);
	void UseItem(Position position, Player* target = nullptr);
	Item* findItem(int id);
	Position findItemPos(int id);
	int findItemCount(int id);
	void SetToShortCut(Bag* target);
	void Sort();
	map<Position, Item*>& GetItems();


public:

	virtual void Display();

	virtual void AcceptKbEvent(char key);

private:
	_SYSTEM_PRIVATE_(int, MaxX, maxX);
	_SYSTEM_PRIVATE_(int, MaxY, maxY);
	_SYSTEM_PRIVATE_(bool, ShowItemDescribe, showItemDescribe);
	_SYSTEM_PRIVATE_(Position, CurPos, curPos);
	_SYSTEM_PRIVATE_(Player*, Owner, owner);
	map<Position, Item*> items;
};
