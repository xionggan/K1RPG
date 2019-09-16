#pragma once 
#include "Block.h";


class Bullet : public Walkable
{
public:

	Bullet(Position* _position, MoveDir moveDir, int width = 1, int height = 1, int type = MT_BULLET);

	~Bullet();

	virtual void Update();

private:
	_SYSTEM_PRIVATE_(int, Atk, atk);
	_SYSTEM_PRIVATE_(MoveDir, MoveDir, moveDir);
	_SYSTEM_PRIVATE_(GameObject*, Owner, owner);
	_SYSTEM_PRIVATE_(int, IntervalFrame, intervalFrame);
};