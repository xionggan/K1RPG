#include "Unity.h"

Block::Block(Position* _position, int width, int height, int type) : GameObject(_position, width, height, type)
{
	SetBgColor(8);
	GetPicture()[0] = "¡ö";
}

Block::~Block()
{

}


void Block::Update()
{
	
}

