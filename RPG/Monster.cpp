#include "Unity.h"

Monster::Monster(Position* _position, int width, int height, int type)
: CombatRole(_position, width, height, type)
{
	frameCount = 0;
	SetFontColor(13);
	GetPicture()[0] = "°Ò°¯°Ò";
}

Monster::Monster(Position* _position, int _width, int _height, char* _pFlag, int _maxHp, int _maxMp, int _atk, int _def)
: CombatRole(_position, _width, _height, _pFlag, _maxHp, _maxMp, _atk, _def)
{

}

Monster::~Monster()
{
}

void Monster::Update(){

	if (Countdown > 0){
		Countdown--;
		if (Countdown == 0){
			ChangeStatus(RoleStatus::RS_NORMAL);
		}
	}

	frameCount++;
	if (frameCount%5 == 0){
		Position moveDir = Position(0, 0);

		switch (rand() % 8)
		{
		case MD_NORTH:
			moveDir.y = -1;
			break;
		case MD_NORTHEAST:
			moveDir.x = 1;
			moveDir.y = -1;
			break;
		case MD_EAST:
			moveDir.x = 1;
			break;
		case MD_SOUTHEAST:
			moveDir.x = 1;
			moveDir.y = 1;
			break;
		case MD_SOUTH:
			moveDir.y = 1;
			break;
		case MD_SOUTHWEST:
			moveDir.x = -1;
			moveDir.y = 1;
			break;
		case MD_WEST:
			moveDir.x = -1;
			break;
		case MD_NORTHWEST:
			moveDir.x = -1;
			moveDir.y = -1;
			break;
		}


		//’œ∞≠ŒÔºÏ≤È,≈–∂œƒ‹∑Ò“∆∂ØŒª÷√
		list<Block*>* wallList = this->GetScene()->FindGameObjectsByTag<Block*>();

		Rect originRect = Rect(*(this->GetRect()));

		Rect targetRect = Rect(new Position(originRect.startPos->x + moveDir.x, originRect.startPos->y + moveDir.y), originRect.width, originRect.height);

		auto iBegin = wallList->begin();

		while (iBegin != wallList->end())
		{
			if (*iBegin == this){
				iBegin++;
				continue;
			}

			if (targetRect.isIntersect((*iBegin)->GetRect()))
			{
				moveDir = Position(0, 0);
			}
			iBegin++;
		}

		this->GetRect()->startPos->x = this->GetRect()->startPos->x + moveDir.x;
		this->GetRect()->startPos->y = this->GetRect()->startPos->y + moveDir.y;


		if (frameCount % 30 == 0){
			frameCount = 0;

			Position* center = this->GetScene()->GetMainPlayer()->GetRect()->getCenterPos();

			Position* cur = this->GetRect()->getCenterPos();

			if (abs(center->x - cur->x)< this->GetScene()->GetViewWidth() / 2 && abs(center->y - cur->y)< this->GetScene()->GetViewHeight() / 2){
				//…‰ª˜
				GameObject* player = this->GetScene()->GetMainPlayer();

				Shoot(player->GetRect()->getCenterPos());
			}
		}
	}
}


void Monster::ChangeStatus(RoleStatus status){
	switch (status)
	{
	case RS_NORMAL:
		SetFontColor(13);
		GetPicture()[0] = "°Ò°¯°Ò";
		break;
	case RS_SHOOTING:
		SetFontColor(14);
		Countdown = 2;
		break;
	case RS_BESHOOT:
		Countdown = 2;
		GetPicture()[0] = "°¡©n°¡";
		break;
	case RS_DEAD:
		{
			Player* player = (Player*)GetScene()->GetMainPlayer();
			player->SetKillCount(player->GetKillCount() + 1);
			Recycle();
		}
		break;
	default:
		break;
	}
	CombatRole::ChangeStatus(status);
}

void Monster::AI(){
}