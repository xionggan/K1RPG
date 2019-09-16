#pragma once 
#include "Block.h";

#include <functional>

class Rect;
class Menu;
class Dialog;
class Shop;

class Npc : public Block
{
public:



	Npc(Position* _position ,int width = 3,int height = 1,int type = MT_NPC);

	~Npc();

	void Update();

	void Talk();

	void TalkFinish();

	void Shopping();

	void ChangeStatus(NpcStatus status);

private:

	Menu* menu;

	Shop* shop;

	Dialog* dialog;

	Rect* triggerRect;

	NpcStatus status;

	int playerCurKillCount;
};