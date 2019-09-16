#pragma once
#include"Frame.h"
#include "CombatRole.h"

class Bag;
class ShortcutBag;
class Item;
class Equipment;
class PauseMenu;

class Player : public CombatRole
{

public:
	Player(Position* _position,int width = 3,int height = 3,int type = MT_PLAYER);

	Player(Position* _position,int width,int height,char* pFlag, int maxHp, int maxMp, int atk, int def);

	~Player();

	void UsedItem(Item* item);

	void ShowInfo();

	void ChangePicture();

public:

	virtual void Update();

	virtual void ChangeStatus(RoleStatus status);

private:
	_SYSTEM_PRIVATE_(Bag*, ItemBag, itemBag);

	_SYSTEM_PRIVATE_(ShortcutBag*, CutBag, cutBag);

	_SYSTEM_PRIVATE_(Equipment*, Weapon, weapon);

	_SYSTEM_PRIVATE_(Equipment*, Armor, armor);

	_SYSTEM_PRIVATE_(bool, EquipArmor, isEquipArmor);

	_SYSTEM_PRIVATE_(Bullet*, DrillBullet, drillBullet);

	_SYSTEM_PRIVATE_(int, Coin, coin);

	_SYSTEM_PRIVATE_(int, KillCount, killCount);

	_SYSTEM_PRIVATE_(PauseMenu*,PauseMenu, pauseMenu);

};