#include "Unity.h"


Walkable::Walkable(Position* _position, int width, int height, int type) : GameObject(_position, width, height, type)
{
	SetFontColor(10);
	GetPicture()[0] = "::";
}

Walkable::~Walkable()
{

}


void Walkable::Update()
{

}
