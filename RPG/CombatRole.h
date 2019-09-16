#pragma once
#include"Frame.h"
#include "Block.h"
#include "GameLib.h"

class Bullet;

class CombatRole : public Block
{

public:
	CombatRole(Position* _position,int width = 3,int height = 1,int type = MT_MONSTER);
	CombatRole(Position* _position, int width , int height, char* pFlag, int maxHp, int maxMp, int atk, int def);
	~CombatRole();

	//自己中心点生成子弹朝某个方向发射
	void Shoot(MoveDir dir);

	//从某个点生成子弹向某个方向发射
	void CombatRole::Shoot(Position* origin, MoveDir dir);

	//朝某个点射击
	void Shoot(Position* target);

	//被射击
	void BeShoot(Bullet* bullet);

public:

	virtual void Update() = 0;

	virtual void ChangeStatus(RoleStatus status){
		roleStatus = status;
	}

	int Countdown;

	int frameCount;

private:
	_SYSTEM_PRIVATE_(char*, Flag, pFlag);
	_SYSTEM_PRIVATE_(int, MaxHp, maxHp);
	_SYSTEM_PRIVATE_(int, MaxMp, maxMp);
	_SYSTEM_PRIVATE_(int, Hp, hp);
	_SYSTEM_PRIVATE_(int, Mp, mp);
	_SYSTEM_PRIVATE_(int, Atk, atk);
	_SYSTEM_PRIVATE_(int, Def, def);
	_SYSTEM_PRIVATE_(MoveDir, MoveDir, moveDir);
	_SYSTEM_PRIVATE_READONLY_(RoleStatus, RoleStatus, roleStatus);
	_SYSTEM_PRIVATE_(BulletType, BulletType, bulletType);
};