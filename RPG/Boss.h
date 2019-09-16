#pragma once 
#include "Monster.h";


class Boss : public Monster
{
public:

	Boss(Position* _position,int width = 8, int height = 1,int type = MT_BOSS);

	Boss(Position* _position, int width, int height, char* pFlag, int maxHp, int maxMp, int atk, int def);

	~Boss();

public:

	virtual void Update();

	virtual void ChangeStatus(RoleStatus status);

	virtual void AI();

	void GameOver();

	void BackTitle();
};