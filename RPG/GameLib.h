#pragma once
enum MapType
{
	MT_WALL,
	MT_STONE,
	MT_MONSTER,
	MT_BOSS,
	MT_NPC,
	MT_PLAYER,
	MT_GATEWAY,
	MT_BULLET,
	MT_GRASS,
	MT_ITEM,
};

enum MoveDir
{
	MD_NORTH,
	MD_NORTHEAST,
	MD_EAST,
	MD_SOUTHEAST,
	MD_SOUTH,
	MD_SOUTHWEST,
	MD_WEST,
	MD_NORTHWEST,
};


enum RoleStatus
{
	RS_NORMAL,
	RS_SHOOTING,
	RS_BESHOOT,
	RS_DEAD,
};

enum BulletType
{
	BT_NORMAL,
	BT_LASER,
	BT_FROZEN,
	BT_REPEL
};


enum ItemType
{
	IT_DRILL,
	IT_CANNON,
	IT_LASERGUN,
	IT_WALLBUILDER,
	IT_REACTIVEARMOR,
	IT_HP,
	IT_AMMO,
	IT_STONE,
};

enum EquipmentType
{
	ET_WEAPON,
	ET_ARMOR
};


enum NpcStatus
{
	NS_WAITTASK,
	NS_INTASK,
	NS_FINISHTASK,
	NS_NORMAL
};