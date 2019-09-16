#pragma once 
#include "CombatRole.h";


class Monster : public CombatRole
{
public:

	Monster(Position* _position,int width = 3,int height = 1,int type = MT_MONSTER);

	Monster(Position* _position, int width, int height, char* pFlag, int maxHp, int maxMp, int atk, int def);

	~Monster();

public:

	virtual void Update();

	virtual void ChangeStatus(RoleStatus status);

	virtual void AI();

};