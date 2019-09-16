#include"Unity.h"

Player::Player(Position* _position, int _width, int _height, int _type) : CombatRole(_position, _width, _height, _type)
{
	itemBag = new Bag(this, new Position(1, 1), 5, 3);

	itemBag->AddItem(ItemFactory::GetInstance()->CreateItem(ItemType::IT_DRILL));

	cutBag = new ShortcutBag(this, new Position(15, 32));
	SetAtk(0);
	SetFontColor(11);
	weapon = nullptr;
	armor = nullptr;
	itemBag->UseItem();
	drillBullet = new Bullet(new Position(0, 0), MoveDir::MD_NORTH);
	drillBullet->SetOwner(this);
	drillBullet->SetAtk(5);
	ChangePicture();
	coin = 100;
	killCount = 0;

	pauseMenu = nullptr;
}

Player::Player(Position* _position, int _width, int _height, char* _pFlag, int _maxHp, int _maxMp, int _atk, int _def) 
: CombatRole(_position, _width, _height, _pFlag, _maxHp, _maxMp, _atk, _def)
{
	itemBag = new Bag(this, new Position(1, 1), 5, 3);
	cutBag = new ShortcutBag(this, new Position(15, 32));
	SetAtk(0);
	SetFontColor(11);
	weapon = nullptr;
	armor = nullptr;
	drillBullet = new Bullet(new Position(0, 0), MoveDir::MD_NORTH);
	drillBullet->SetOwner(this);
	drillBullet->SetAtk(1);
	ChangePicture();
	coin = 0;
	killCount = 0;
}

Player::~Player(){
	_RELEASE_SAFE_(itemBag);
	_RELEASE_SAFE_(cutBag);
	_RELEASE_SAFE_(pauseMenu);
}

void Player::UsedItem(Item* item){
	item->Effect(this);
}

void Player::Update(){

	frameCount++;

	if (frameCount == 100){
		frameCount = 0;
	}

	if (Countdown > 0){
		Countdown--;
		if (Countdown == 0){
			ChangeStatus(RoleStatus::RS_NORMAL);
		}
	}

	auto windowList = GetScene()->GetWindowList();


	char key = NULL;
	if (kbhit()){
		key = getch();
		if (windowList->size() > 0){
			windowList->back()->AcceptKbEvent(key);
			return;
		}

		GetScene()->GetCutUI()->AcceptKbEvent(key);
	}

	if (windowList->size() > 0){
		return;
	}

	Position moveDirPos = Position(0, 0);

	if (GetKeyState('W') & 0x8000 && !(GetKeyState('D') & 0x8000) && !(GetKeyState('A') & 0x8000))		//获取某键是否按下
	{
		if (GetMoveDir() != MD_NORTH){
			SetMoveDir(MD_NORTH);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.y = -1;
		}
	}
	else if (GetKeyState('W') & 0x8000 && GetKeyState('D') & 0x8000){
		if (GetMoveDir() != MD_NORTHEAST){
			SetMoveDir(MD_NORTHEAST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = 1;
			moveDirPos.y = -1;
		}
	}
	else if (GetKeyState('D') & 0x8000 && !(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000))
	{
		if (GetMoveDir() != MD_EAST){
			SetMoveDir(MD_EAST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = 1;
		}
	}
	else if (GetKeyState('D') & 0x8000 && GetKeyState('S') & 0x8000)
	{
		if (GetMoveDir() != MD_SOUTHEAST){
			SetMoveDir(MD_SOUTHEAST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = 1;
			moveDirPos.y = 1;
		}
	}
	else if (GetKeyState('S') & 0x8000 && !(GetKeyState('D') & 0x8000) && !(GetKeyState('A') & 0x8000))
	{
		if (GetMoveDir() != MD_SOUTH){
			SetMoveDir(MD_SOUTH);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.y = 1;
		}
	}
	else if (GetKeyState('S') & 0x8000 && GetKeyState('A') & 0x8000)
	{
		if (GetMoveDir() != MD_SOUTHWEST){
			SetMoveDir(MD_SOUTHWEST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = -1;
			moveDirPos.y = 1;
		}
	}
	else if (GetKeyState('A') & 0x8000 && !(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000))
	{
		if (GetMoveDir() != MD_WEST){
			SetMoveDir(MD_WEST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = -1;
		}
	}
	else if (GetKeyState('A') & 0x8000 && GetKeyState('W') & 0x8000)
	{
		if (GetMoveDir() != MD_NORTHWEST){
			SetMoveDir(MD_NORTHWEST);
			ChangePicture();
			return;
		}
		else{
			moveDirPos.x = -1;
			moveDirPos.y = -1;
		}
	}
	else if (GetKeyState('J') & 0x8000){
		if (weapon->GetId() == IT_CANNON){
			if (frameCount % 2 == 0){
				Position p = GetItemBag()->findItemPos(IT_AMMO);
				SetBulletType(BulletType::BT_NORMAL);

				if (p.x >= 0 && p.y >= 0){
					Shoot(GetMoveDir());
					GetItemBag()->UseItem(p);
					PlaySound(TEXT(".\\Sounds\\发射炮弹.wav"), NULL, SND_ASYNC);
				}
				else{
					PlaySound(TEXT(".\\Sounds\\弹药耗尽.wav"), NULL, SND_ASYNC);
				}
			}
		}else if (weapon->GetId() == IT_DRILL){
			PlaySound(TEXT(".\\Sounds\\挖掘.wav"), NULL, SND_ASYNC);
			Rect* targetRect = nullptr;
			switch (GetMoveDir())
			{
			case MD_NORTH:
				targetRect = new Rect(new Position(this->GetRect()->getCenterPos()->x - 1, this->GetRect()->getCenterPos()->y - 2), 3, 1);
				break;
			case MD_EAST:
				targetRect = new Rect(new Position(this->GetRect()->getCenterPos()->x + 2, this->GetRect()->getCenterPos()->y - 1), 1, 3);
				break;
			case MD_SOUTH:
				targetRect = new Rect(new Position(this->GetRect()->getCenterPos()->x - 1, this->GetRect()->getCenterPos()->y + 2), 3, 1);
				break;
			case MD_WEST:
				targetRect = new Rect(new Position(this->GetRect()->getCenterPos()->x - 2, this->GetRect()->getCenterPos()->y - 1), 1, 3);
				break;
			default:
				return;
			}
			//障碍物检查,摧毁前方的方块
			list<Block*>* wallList = this->GetScene()->FindGameObjectsByTag<Block*>();
			auto iBegin = wallList->begin();

			while (iBegin != wallList->end())
			{
				if (*iBegin == this){
					iBegin++;
					continue;
				}

				if (targetRect->isIntersect((*iBegin)->GetRect()))
				{

					Monster* monster = dynamic_cast<Monster*>(*iBegin);
					if (monster != NULL){
						monster->BeShoot(drillBullet);
					}

					Stone* stone = dynamic_cast<Stone*>(*iBegin);
					if (stone != NULL){
						stone->BeHurt();
					}
				}
				iBegin++;
			}
		} else if (weapon->GetId() == IT_WALLBUILDER){

			Position* targetPositon = new Position(this->GetRect()->getCenterPos()->x, this->GetRect()->getCenterPos()->y);

			switch (GetMoveDir())
			{
			case MoveDir::MD_NORTH:
				targetPositon->y -= 2;
				break;
			case MoveDir::MD_NORTHEAST:
				targetPositon->x += 2;
				targetPositon->y -= 2;
				break;
			case MoveDir::MD_EAST:
				targetPositon->x += 2;
				break;
			case MoveDir::MD_SOUTHEAST:
				targetPositon->x += 2;
				targetPositon->y += 2;
				break;
			case MoveDir::MD_SOUTH:
				targetPositon->y += 2;
				break;
			case MoveDir::MD_SOUTHWEST:
				targetPositon->x -= 2;
				targetPositon->y += 2;
				break;
			case MoveDir::MD_WEST:
				targetPositon->x -= 2;
				break;
			case MoveDir::MD_NORTHWEST:
				targetPositon->x -= 2;
				targetPositon->y -= 2;
				break;
			default:
				break;
			}

			Position p = GetItemBag()->findItemPos(IT_STONE);

			if (p.x < 0 || p.y < 0){
				PlaySound(TEXT(".\\Sounds\\弹药耗尽.wav"), NULL, SND_ASYNC);
				return;
			}

			Stone* stone = new Stone(targetPositon);

			list<Block*>* wallList = this->GetScene()->FindGameObjectsByTag<Block*>();

			auto iBegin = wallList->begin();

			while (iBegin != wallList->end())
			{
				if (stone->GetRect()->isIntersect((*iBegin)->GetRect()))
				{
					delete(stone);
					return;
				}
				iBegin++;
			}
			stone->Bind(this->GetScene());
			GetItemBag()->UseItem(p);
			PlaySound(TEXT(".\\Sounds\\造墙.wav"), NULL, SND_ASYNC);
		}
		else if (weapon->GetId() == IT_LASERGUN){

			Position p = GetItemBag()->findItemPos(IT_AMMO);
			SetBulletType(BulletType::BT_LASER);

			if (p.x >= 0 && p.y >= 0){
				Shoot(GetMoveDir());
				GetItemBag()->UseItem(p);
				PlaySound(TEXT(".\\Sounds\\发射激光.wav"), NULL, SND_ASYNC);
			}
			else{
				PlaySound(TEXT(".\\Sounds\\弹药耗尽.wav"), NULL, SND_ASYNC);
			}
		}
	}
	else if (key == 'c'){
		itemBag->Bind(GetScene());
		return;
	}

	else if (key == 27){
		if (pauseMenu == nullptr){
			pauseMenu = new PauseMenu(GetScene(),"菜单",new Position(20,10));
		}
		pauseMenu->Bind(GetScene());
		return;
	}

	if (moveDirPos == Position(0, 0)){
		return;
	}
	
	//障碍物检查,判断能否移动位置
	list<Block*>* wallList = this->GetScene()->FindGameObjectsByTag<Block*>();

	Rect originRect = Rect(*(this->GetRect()));

	Rect targetRect = Rect(new Position(originRect.startPos->x + moveDirPos.x, originRect.startPos->y + moveDirPos.y), originRect.width, originRect.height);

	auto iBegin = wallList->begin();

	while (iBegin != wallList->end())
	{
		if (*iBegin == this){
			iBegin++;
			continue;
		}

		if (targetRect.isIntersect((*iBegin)->GetRect()))
		{
			moveDirPos = Position(0, 0);
		}
		iBegin++;
	}

	this->GetRect()->startPos->x = this->GetRect()->startPos->x + moveDirPos.x;
	this->GetRect()->startPos->y = this->GetRect()->startPos->y + moveDirPos.y;
}

void Player::ChangeStatus(RoleStatus status){
	switch (status)
	{
	case RS_NORMAL:
		SetFontColor(11);
		break;
	case RS_SHOOTING:
		SetFontColor(14);
		Countdown = 2;
		break;
	case RS_BESHOOT:
		SetFontColor(12);
		Countdown = 2;
		break;
	case RS_DEAD:
	{
					// 暂停
					mciSendString(TEXT("close background "), NULL, 0, NULL);

					PlaySound(TEXT(".\\Sounds\\GameOver.wav"), NULL, SND_ASYNC);

					Menu* menu = new Menu("游戏结束", new Position(16, 10),10,8);

					Option* option = new BackTitleOption("返回标题页面");
					
					menu->AddOption(option);

					option = new ExitOption("退出程序");

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

void Player::ChangePicture(){

	bool isEquipArmor = armor != nullptr && armor->GetId() == IT_REACTIVEARMOR;

	bool isEquipDrill = weapon != nullptr && weapon->GetId() == IT_DRILL;

	if (isEquipArmor){
		GetPicture()[0] = "◤━◥";
		GetPicture()[2] = "◣━◢";
	}
	else{
		GetPicture()[0] = "┏━┓";
		GetPicture()[2] = "┗━┛";
	}

	switch (GetMoveDir())
	{
	case MD_NORTH:
		GetPicture()[1] = "┃↑┃";
		if (isEquipDrill){
			GetPicture()[0] = isEquipArmor? "◤∧◥" : "┏∧┓";
		}
		break;
	case MD_NORTHEAST:
		GetPicture()[1] = "┃↗┃";
		break;
	case MD_EAST:
		if (isEquipDrill){
			GetPicture()[1] = "┃→＞";
		}
		else{
			GetPicture()[1] = "┃→┃";
		}
		break;
	case MD_SOUTHEAST:
		GetPicture()[1] = "┃↘┃";
		break;
	case MD_SOUTH:
		GetPicture()[1] = "┃↓┃";
		if (isEquipDrill){
			GetPicture()[2] = isEquipArmor ? "◣∨◢" : "┗∨┛";
		}
		break;
	case MD_SOUTHWEST:
		GetPicture()[1] = "┃↙┃";
		break;
	case MD_WEST:
		if (isEquipDrill){
			GetPicture()[1] = "＜←┃";
		}
		else{
			GetPicture()[1] = "┃←┃";
		}
		break;
	case MD_NORTHWEST:
		GetPicture()[1] = "┃↖┃";
		break;
	}
}
