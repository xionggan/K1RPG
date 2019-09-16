#include "Unity.h"
#include "tinyxml\tinyxml.h"

DrakPrairie::DrakPrairie()
:Scene(2,"∫⁄∞µ≤›‘≠", new Position(0, 0), 40, 30)
{
	SetViewRange(8);
}

DrakPrairie::~DrakPrairie()
{

}

void DrakPrairie::Init()
{

	if (GetGameObjectList()->size() == 0){
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
						pGameObjectLoopCur = new Walkable(new Position(i, j));
						pGameObjectLoopCur->Bind(this);
					}
				}
			}
		}
		RandomAddGameObject(MT_BOSS, 1);
		RandomAddGameObject(MT_PLAYER, 1);
	}

	SetInfoUI(new PlayerInfoUI(nullptr, new Position(42, 0)));
	Player* player = (Player*)(this->GetMainPlayer());
	GetInfoUI()->SetPlayer(player);
	SetCutUI(player->GetCutBag());
	DrawBorder();

	// ‘›Õ£
	mciSendString( TEXT( "close background " ), NULL, 0, NULL );
	// “Ù¿÷ mp3
	WCHAR mciCmd[] = TEXT("open ./Sounds/Boss±≥æ∞“Ù¿÷.mp3 alias background"); //.mp3∏Ò Ωµƒ
	mciSendString(mciCmd, NULL, 0, NULL);
	mciSendString(TEXT("play background repeat"), NULL, 0, NULL);

}


void DrakPrairie::RandomAddGameObject(MapType type, int count){
	for (int i = 0; i < count; i++){
		GameObject* gameObject = nullptr;
		switch (type)
		{
		case MT_PLAYER:
			gameObject = new Player(new Position(0, 0));
			this->SetMainPlayer(gameObject);
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

void DrakPrairie::Display(){
	GetInfoUI()->Display();
	GetCutUI()->Display();
	Scene::Display();
}

void DrakPrairie::Load()
{
	auto pPlayer = this->FindGameObjectsByTag<Player*>()->front();

	Bag* itemBag = pPlayer->GetItemBag();

	Bag* cutBag = pPlayer->GetCutBag();

	TiXmlDocument doc;

	bool bLoad = doc.LoadFile("File/Player/PlayerInfo.xml");

	if (bLoad)
	{
		auto pPlayerEle = doc.FirstChildElement("Player");

		int hp = atoi(pPlayerEle->Attribute("hp"));

		int coin = atoi(pPlayerEle->Attribute("coin"));

		pPlayer->SetHp(hp);

		pPlayer->SetCoin(coin);

		int weaponId = atoi(pPlayerEle->Attribute("weaponId"));

		int armorId = atoi(pPlayerEle->Attribute("armorId"));

		auto pItemBagEle = pPlayerEle->FirstChildElement("itemBag");

		for (TiXmlElement* pItemEle = pItemBagEle->FirstChildElement();pItemEle != nullptr;pItemEle = pItemEle->NextSiblingElement()){
			int itemId = atoi(pItemEle->Attribute("id"));
			int x = atoi(pItemEle->Attribute("x"));
			int y = atoi(pItemEle->Attribute("y"));
			int count = atoi(pItemEle->Attribute("count"));
			itemBag->AddItem(Position(x, y), ItemFactory::GetInstance()->CreateItem((ItemType)itemId, count));
			if (itemId == weaponId || itemId == armorId){
				itemBag->UseItem(Position(x, y));
			}
		}

		auto pCutBagEle = pPlayerEle->FirstChildElement("cutBag");

		for (TiXmlElement* pItemEle = pCutBagEle->FirstChildElement(); pItemEle != nullptr; pItemEle = pItemEle->NextSiblingElement()){
			int itemId = atoi(pItemEle->Attribute("id"));
			int x = atoi(pItemEle->Attribute("x"));
			int y = atoi(pItemEle->Attribute("y"));
			int count = atoi(pItemEle->Attribute("count"));
			cutBag->AddItem(Position(x, y),itemBag->findItem(itemId));
		}
	}
}