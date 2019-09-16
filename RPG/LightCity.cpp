#include "Unity.h"

LightCity::LightCity()
:Scene("光明之城",new Position(0,0),40, 30)
{

}

LightCity::~LightCity()
{

}

void LightCity::Init()
{
	for (size_t i = 0; i < GetMaxX(); i++)
	{
		for (size_t j = 0; j < GetMaxY(); j++)
		{
			GameObject* pGameObjectLoopCur = nullptr;
			GameObject* road = nullptr;
			if (i == 0 || j == 0 || i == GetMaxX() - 1 || j == GetMaxY() - 1){
				pGameObjectLoopCur = new Block(new Position(i, j));
				pGameObjectLoopCur->Bind(this);
			}
			else{
				int random = rand() % 100;
				if (random>95){
					pGameObjectLoopCur = new Block(new Position(i, j));
					pGameObjectLoopCur->Bind(this);
					Block* pBlockLoopCur = dynamic_cast<Block* >(pGameObjectLoopCur);
					pBlockLoopCur->SetDestroyable(true);
				}
				else if (random>90){
					pGameObjectLoopCur = new Walkable(new Position(i, j));
					pGameObjectLoopCur->Bind(this);
				} 
			}
		}
	}
	infoUI = new PlayerInfoUI(nullptr, new Position(42, 0));
	cutUI = nullptr;
	RandomAddGameObject(MT_MONSTER,3);
	RandomAddGameObject(MT_NPC, 1);
	RandomAddGameObject(MT_BOSS, 1);
	RandomAddGameObject(MT_PLAYER, 1);
	DrawBorder();
}


void LightCity::RandomAddGameObject(MapType type,int count){
	for (int i = 0; i < count; i++){
		GameObject* gameObject = nullptr;
		switch (type)
		{
		case MT_PLAYER:
			gameObject = new Player(new Position(0, 0));
			this->SetMainPlayer(gameObject);
			infoUI->SetPlayer((Player*)gameObject);
			cutUI = ((Player*)gameObject)->GetCutBag();;
			break;
		case MT_MONSTER:
			gameObject = new Monster(new Position(0, 0));
			break;
		case MT_NPC:
			gameObject = new Npc(new Position(0, 0));
			break;
		case MT_BOSS:
			gameObject = new Boss(new Position(0, 0));
			break;
		}

		int width = gameObject->GetRect()->width;
		int height = gameObject->GetRect()->height;
		gameObject->GetRect()->startPos->x = rand() % (GetMaxX() - 2 - width) + 1;
		gameObject->GetRect()->startPos->y = rand() % (GetMaxY() - 2 - height) + 1;

		list<Block*>* wallList = this->FindGameObjectsByTag<Block*>();

		auto iBegin = wallList->begin();

		while (iBegin != wallList->end())
		{
			if (gameObject->GetRect()->isIntersect((*iBegin)->GetRect()))
			{
				gameObject->GetRect()->startPos->x = rand() % (GetMaxX() - 2 - width) + 1;
				gameObject->GetRect()->startPos->y = rand() % (GetMaxY() - 2 - height) + 1;
				iBegin = wallList->begin();
				continue;
			}
			iBegin++;
		}
		gameObject->Bind(this);
	}
}

void LightCity::Display(){
	infoUI->Display();
	cutUI->Display();
	Scene::Display();
}