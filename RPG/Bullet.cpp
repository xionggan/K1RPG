#include "Unity.h"

Bullet::Bullet(Position* _position, MoveDir _moveDir, int _width, int _height, int _type)
: Walkable(_position, _width, _height, _type)
{
	atk = 10;
	moveDir = _moveDir;
	SetFontColor(15);
	GetPicture()[0] = "¡ñ";
	intervalFrame = 2;
}

Bullet::~Bullet()
{
}

void Bullet::Update(){
	Position moveDirPos = Position(0, 0);
	switch (moveDir)
	{
	case MD_NORTH:
		moveDirPos.y = -1;
		break;
	case MD_NORTHEAST:
		moveDirPos.x = 1;
		moveDirPos.y = -1;
		break;
	case MD_EAST:
		moveDirPos.x = 1;
		break;
	case MD_SOUTHEAST:
		moveDirPos.x = 1;
		moveDirPos.y = 1;
		break;
	case MD_SOUTH:
		moveDirPos.y = 1;
		break;
	case MD_SOUTHWEST:
		moveDirPos.x = -1;
		moveDirPos.y = 1;
		break;
	case MD_WEST:
		moveDirPos.x = -1;
		break;
	case MD_NORTHWEST:
		moveDirPos.x = -1;
		moveDirPos.y = -1;
		break;
	}

	//ÕÏ°­Îï¼ì²é,ÅÐ¶ÏÄÜ·ñÅö×²
	list<Block*>* wallList = this->GetScene()->FindGameObjectsByTag<Block*>();

	Rect originRect = Rect(*(this->GetRect()));

	Rect targetRect = Rect(new Position(originRect.startPos->x + moveDirPos.x, originRect.startPos->y + moveDirPos.y), originRect.width, originRect.height);

	auto iBegin = wallList->begin();

	while (iBegin != wallList->end())
	{

		if (targetRect.isIntersect((*iBegin)->GetRect()) && this->owner != (*iBegin))
		{
			Player* player = dynamic_cast<Player*>(*iBegin);
			Monster* monster = dynamic_cast<Monster*>(*iBegin);
			if (player != NULL && player != owner){
				player->BeShoot(this);
			}
			if (monster != NULL && monster != owner){
				monster->BeShoot(this);
			}
			this->Recycle();
			return;
		}
		iBegin++;
	}

	this->GetRect()->startPos->x = this->GetRect()->startPos->x + moveDirPos.x;
	this->GetRect()->startPos->y = this->GetRect()->startPos->y + moveDirPos.y;

}