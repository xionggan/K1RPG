#include "Unity.h"
#include "tinyxml\tinyxml.h"

HillyLand::HillyLand()
:Scene(1,"«¡Íµÿ¥¯",new Position(0,0),60, 45)
{

}

HillyLand::~HillyLand()
{
}

void HillyLand::Init()
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
						pGameObjectLoopCur = new Stone(new Position(i, j));
						pGameObjectLoopCur->Bind(this);
					}
					else if (random>90){
						pGameObjectLoopCur = new Walkable(new Position(i, j));
						pGameObjectLoopCur->Bind(this);
					}
				}
			}
		}
		RandomAddGameObject(MT_MONSTER, 6);
		RandomAddGameObject(MT_NPC, 1);
		RandomAddGameObject(MT_PLAYER, 1);
	}

	SetInfoUI(new PlayerInfoUI(nullptr, new Position(42, 0)));
	Player* player = (Player*)(this->GetMainPlayer());
	GetInfoUI()->SetPlayer(player);
	SetCutUI((player)->GetCutBag());
	DrawBorder();

	// ‘›Õ£
	mciSendString(TEXT("close background "), NULL, 0, NULL);
	// “Ù¿÷ mp3
	WCHAR mciCmd[] = TEXT("open ./Sounds/±≥æ∞“Ù¿÷.mp3 alias background"); //.mp3∏Ò Ωµƒ
	mciSendString(mciCmd, NULL, 0, NULL);
	mciSendString(TEXT("play background repeat"), NULL, 0, NULL);
}


void HillyLand::RandomAddGameObject(MapType type, int count){
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
		case MT_GATEWAY:
			gameObject = new GateWay(new Position(0, 0));
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

void HillyLand::Display(){
	GetInfoUI()->Display();
	GetCutUI()->Display();
	Scene::Display();
}

void HillyLand::Save()
{
	auto pPlayer = this->FindGameObjectsByTag<Player*>()->front();

	TiXmlDocument doc;

	TiXmlElement* pPlayerEle = new TiXmlElement("Player");

	pPlayerEle->SetAttribute("hp", pPlayer->GetHp());

	pPlayerEle->SetAttribute("coin", pPlayer->GetCoin());

	pPlayerEle->SetAttribute("weaponId", pPlayer->GetWeapon()->GetId());

	pPlayerEle->SetAttribute("armorId", pPlayer->GetArmor() != nullptr ? pPlayer->GetArmor()->GetId(): -1 );

	Bag* itemBag = pPlayer->GetItemBag();

	Bag* cutBag = pPlayer->GetCutBag();

	TiXmlElement* pItemBagEle = new TiXmlElement("itemBag");

	auto begin = itemBag->GetItems().begin();

	while (begin != itemBag->GetItems().end()){
		Item* temp = (*begin).second;
		TiXmlElement* pItemEle = new TiXmlElement("item");
		pItemEle->SetAttribute("id", temp->GetId());
		pItemEle->SetAttribute("x", (*begin).first.x);
		pItemEle->SetAttribute("y", (*begin).first.y);
		Consumables* cTemp = dynamic_cast<Consumables*>(temp);
		if (cTemp != NULL){
			pItemEle->SetAttribute("count", cTemp->GetCount());
		}
		else{
			pItemEle->SetAttribute("count", 1);
		}
		pItemBagEle->LinkEndChild(pItemEle);
		begin++;
	}

	TiXmlElement* pCutBagEle = new TiXmlElement("cutBag");

	begin = cutBag->GetItems().begin();

	while (begin != cutBag->GetItems().end()){
		Item* temp = (*begin).second;
		TiXmlElement* pItemEle = new TiXmlElement("item");
		pItemEle->SetAttribute("id", temp->GetId());
		pItemEle->SetAttribute("x", (*begin).first.x);
		pItemEle->SetAttribute("y", (*begin).first.y);
		Consumables* cTemp = dynamic_cast<Consumables*>(temp);
		if (cTemp != NULL){
			pItemEle->SetAttribute("count", cTemp->GetCount());
		}
		else{
			pItemEle->SetAttribute("count", 1);
		}
		pCutBagEle->LinkEndChild(pItemEle);
		begin++;
	}

	pPlayerEle->LinkEndChild(pItemBagEle);

	pPlayerEle->LinkEndChild(pCutBagEle);

	doc.LinkEndChild(pPlayerEle);

	doc.SaveFile("File/Player/PlayerInfo.xml");
}