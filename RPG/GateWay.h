#pragma once
#include "Frame.h"

class GateWay : public Walkable
{
public:

	GateWay(Position* _position, int width = 3, int height = 3, int type = MT_GATEWAY);

	~GateWay();

public:

	virtual void Update();

private:


};

