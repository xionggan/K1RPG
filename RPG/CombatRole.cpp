#include"Unity.h"

CombatRole::CombatRole(Position* _position, int _width, int _height, int _type) : Block(_position, _width, _height, _type)
{
	pFlag = new char[strlen("战斗角色") + 1];
	strcpy(pFlag, "战斗角色");
	maxHp = 100;
	maxMp = 100;
	hp = maxHp;
	mp = maxMp;
	atk = 10;
	def = 0;
	moveDir = MD_NORTH;
	bulletType = BulletType::BT_NORMAL;
	SetBgColor(0);
}

CombatRole::CombatRole(Position* _position, int _width, int _height, char* _pFlag, int _maxHp, int _maxMp, int _atk, int _def) : Block(_position, _width, _height)
{
	pFlag = new char[strlen(_pFlag) + 1];
	strcpy(pFlag, _pFlag);
	maxHp = _maxHp;
	maxMp = _maxMp;
	hp = maxHp;
	mp = maxMp;
	atk = _atk;
	def = _def;
	moveDir = MD_NORTH;
	bulletType = BulletType::BT_NORMAL;
}

CombatRole::~CombatRole(){
	_RELEASE_SAFE_(pFlag);
}

void CombatRole::Shoot(MoveDir dir){
	Bullet* bullet = nullptr;
	if (bulletType == BulletType::BT_LASER){
		bullet = new LaserBullet(
			new Position(this->GetRect()->getCenterPos()->x,
			this->GetRect()->getCenterPos()->y), dir);
	}else{
		bullet = new Bullet(
			new Position(this->GetRect()->getCenterPos()->x,
			this->GetRect()->getCenterPos()->y), dir);
	}
	bullet->SetOwner(this);
	bullet->Bind(this->GetScene());
	ChangeStatus(RoleStatus::RS_SHOOTING);
}

void CombatRole::Shoot(Position* origin,MoveDir dir){
	Bullet* bullet = new Bullet(origin, dir);
	bullet->SetOwner(this);
	bullet->Bind(this->GetScene());
	ChangeStatus(RoleStatus::RS_SHOOTING);
}

void CombatRole::Shoot(Position* target){

	Position pos = *target - *(this->GetRect()->getCenterPos());
	MoveDir dir = MoveDir::MD_NORTH;
	if (pos.x > 0 && pos.y > 0){
		dir = MoveDir::MD_SOUTHEAST;
	}
	else if (pos.x > 0 && pos.y < 0){
		dir = MoveDir::MD_NORTHEAST;
	}
	else if (pos.x < 0 && pos.y > 0){
		dir = MoveDir::MD_SOUTHWEST;
	}
	else if (pos.x < 0 && pos.y < 0){
		dir = MoveDir::MD_NORTHWEST;
	}
	else if (pos.x = 0 && pos.y > 0){
		dir = MoveDir::MD_SOUTH;
	}
	else if (pos.x = 0 && pos.y < 0){
		dir = MoveDir::MD_NORTH;
	}
	else if (pos.y = 0 && pos.x > 0){
		dir = MoveDir::MD_EAST;
	}
	else if (pos.y = 0 && pos.x < 0){
		dir = MoveDir::MD_WEST;
	}

	Bullet* bullet = new Bullet(
		new Position(this->GetRect()->getCenterPos()->x,
		this->GetRect()->getCenterPos()->y), dir);
	bullet->SetOwner(this);
	bullet->Bind(this->GetScene());
	ChangeStatus(RoleStatus::RS_SHOOTING);
}


void CombatRole::BeShoot(Bullet* bullet){
	if (roleStatus != RS_DEAD){
		SetHp(GetHp() - (bullet->GetAtk() - GetDef()));
		if (GetHp() <= 0){
			SetHp(0);
			ChangeStatus(RoleStatus::RS_DEAD);
		}
		else{
			ChangeStatus(RoleStatus::RS_BESHOOT);
		}
		if (bullet->GetOwner() == GetScene()->GetMainPlayer()){
			Player* player = dynamic_cast<Player*>(GetScene()->GetMainPlayer());
			player->SetCoin(player->GetCoin() + 4);
		}
	}
}