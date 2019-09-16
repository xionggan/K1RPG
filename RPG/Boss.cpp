#include "Unity.h"

Boss::Boss(Position* _position, int _width, int _height, int _type)
: Monster(_position, _width, _height, _type)
{
	frameCount = 0;
	SetFontColor(13);
	GetPicture()[0] = "（＊￣（エ）￣）";
	SetHp(600);
}

Boss::Boss(Position* _position, int _width, int _height, char* _pFlag, int _maxHp, int _maxMp, int _atk, int _def)
: Monster(_position, _width, _height, _pFlag, _maxHp, _maxMp, _atk, _def)
{

}

Boss::~Boss()
{

}

void Boss::Update(){

	if (Countdown > 0){
		Countdown--;
		if (Countdown == 0){
			ChangeStatus(RoleStatus::RS_NORMAL);
		}
	}

	frameCount++;
	if (frameCount % 5 == 0){
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

		//障碍物检查,判断能否移动位置
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


		if (frameCount % 20 == 0){
			frameCount = 0;
			//射击
			Shoot(MoveDir::MD_NORTH);
			Shoot(MoveDir::MD_NORTHEAST);
			Shoot(MoveDir::MD_EAST);
			Shoot(MoveDir::MD_SOUTHEAST);
			Shoot(MoveDir::MD_SOUTH);
			Shoot(MoveDir::MD_SOUTHWEST);
			Shoot(MoveDir::MD_WEST);
			Shoot(MoveDir::MD_NORTHWEST);
		}
	}
}

void Boss::ChangeStatus(RoleStatus status){
	switch (status)
	{
	case RS_NORMAL:
		SetFontColor(13);
		GetPicture()[0] = "（＊￣（エ）￣）";
		break;
	case RS_SHOOTING:
		SetFontColor(14);
		Countdown = 2;
		break;
	case RS_BESHOOT:
		Countdown = 2;
		GetPicture()[0] = "（  ￣（﹏）￣）";
		break;
	case RS_DEAD:
		Recycle();
		{
			// 暂停
			mciSendString(TEXT("close background "), NULL, 0, NULL);

			PlaySound(TEXT(".\\Sounds\\Win.wav"), NULL, SND_ASYNC);

			Menu* menu = new Menu("游戏胜利", new Position(16, 10), 10, 8);

			Option* option = new Option("返回标题页面");

			option->optionCallBack = CC_CALLBACK(Boss::BackTitle, this);

			menu->AddOption(option);

			option = new Option("退出程序");

			option->optionCallBack = CC_CALLBACK(Boss::GameOver, this);

			menu->AddOption(option);

			menu->SetCanCanle(false);

			menu->Bind(GetScene());
		}
		break;
	default:
		break;
	}
	CombatRole::ChangeStatus(status);
}

void Boss::GameOver(){
	Director::GetInstance()->SetLoop(false);
	GotoXY(0, 32);
	exit(0);
}

void Boss::BackTitle(){
	Director::GetInstance()->ReplaceScene(new StartMenu);
}

void Boss::AI(){
}