#pragma once
#include "Frame.h"
#include "GameLib.h"

class Block : public GameObject
{
public:

	Block(Position* _position, int width = 1, int height = 1, int type = MT_WALL);

	~Block();

public:

	virtual void Update();

};

