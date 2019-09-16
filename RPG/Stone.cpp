#include "Unity.h"

Stone::Stone(Position* _position, int width, int height, int type) : Block(_position, width, height, type)
{
	GetPicture()[0] = "¡ö";
}

Stone::~Stone()
{

}


void Stone::BeHurt(){
	ItemObject* itemObject = new ItemObject(ItemFactory::GetInstance()->CreateItem(IT_STONE),
		new Position(GetRect()->startPos->x, GetRect()->startPos->y), GetRect()->width, GetRect()->height);
	itemObject->Bind(GetScene());
	Recycle();
}
