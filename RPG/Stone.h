#pragma once
#include "Frame.h"
#include "GameLib.h"

class Stone : public Block
{
public:

	Stone(Position* _position, int width = 1, int height = 1, int type = MT_STONE);

	~Stone();

	void BeHurt();


};

