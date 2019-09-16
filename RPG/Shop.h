#pragma once
#include<vector>
#include"Window.h" 
using namespace std;

class Item;
class Player;

class Shop : public Window
{
public:

	Shop(string title, Position* _startPos);

	~Shop();

	void init();

	void BuyItem(Player* player);

public:

	virtual void Display();

	virtual void AcceptKbEvent(char key);

private:

	vector<Item*> items;

	int curIndex;
};