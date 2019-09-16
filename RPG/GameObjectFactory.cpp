#include "Unity.h"

GameObjectFactory* GameObjectFactory::instance;

GameObjectFactory::GameObjectFactory()
{
	instance = nullptr;
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObjectFactory* GameObjectFactory::GetInstance(){
	if (instance == nullptr){
		instance = new GameObjectFactory();
	}
	return instance;
}

GameObject* GameObjectFactory::CreateObject(int type){

	GameObject* gameObject = nullptr;

	Position* defaultPos = new Position(0, 0);

	switch (type)
	{
	case MT_BOSS:
		gameObject = new Boss(defaultPos);
		break;
	case MT_BULLET:
		gameObject = new Bullet(defaultPos, MoveDir::MD_NORTH);
		break;
	case MT_GATEWAY:
		gameObject = new GateWay(defaultPos);
		break;
	case MT_GRASS:
		gameObject = new Walkable(defaultPos);
		break;
	case MT_ITEM:
		gameObject = new ItemObject(nullptr, defaultPos);
		break;
	case MT_MONSTER:
		gameObject = new Monster(defaultPos);
		break;
	case MT_NPC:
		gameObject = new Npc(defaultPos);
		break;
	case MT_PLAYER:
		gameObject = new Player(defaultPos);
		break;
	case MT_WALL:
		gameObject = new Block(defaultPos);
		break;
	case MT_STONE:
		gameObject = new Stone(defaultPos);
		break;
	default:
		break;
	}

	return gameObject;
}