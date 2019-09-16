#pragma once
#include "Frame.h"
#include "GameLib.h"

class Walkable : public GameObject
{
public:

	Walkable(Position* _position, int width = 1, int height = 1, int type = MT_GRASS );

	~Walkable();

public:

	virtual void Update();

private:


};

