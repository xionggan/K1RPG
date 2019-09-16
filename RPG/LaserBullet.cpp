#include "Unity.h"




LaserBullet::LaserBullet(Position* _position, MoveDir _moveDir)
:Bullet(_position, _moveDir, 1, 1)
{
	SetAtk(10);
	SetMoveDir(_moveDir);
	SetFontColor(15);
	SetBgColor(14);
	GetPicture()[0] = "¡ö";
	SetIntervalFrame(1);
}

LaserBullet::~LaserBullet()
{
}