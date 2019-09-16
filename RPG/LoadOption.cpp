#include "Unity.h"
#include "tinyxml\tinyxml.h"

LoadOption::LoadOption(string content)
:Option(content)
{
	optionCallBack = CC_CALLBACK(LoadOption::LoadByMenu, this);
}

LoadOption::~LoadOption(){

}

void LoadOption::LoadByMenu()
{

	TiXmlDocument doc;

	//清除场景切换存档,防止角色信息重复设置
	bool bLoad = doc.LoadFile("File/Player/PlayerInfo.xml");

	if (bLoad){
		doc.Clear();
		doc.SaveFile("File/Player/PlayerInfo.xml");
	}

	//加载真正的存档
	bLoad = doc.LoadFile("File/Player/SaveFile.xml");

	if (bLoad)
	{

		Scene* loadScene = nullptr;

		auto pSaveFile = doc.FirstChildElement("SaveFile");

		auto pSceneEle = pSaveFile->FirstChildElement("Scene");

		if (atoi(pSceneEle->Attribute("id")) == 1){
			loadScene = new HillyLand;
		}
		else if (atoi(pSceneEle->Attribute("id")) == 2) {
			loadScene = new DrakPrairie;
		}
		else{
			return;
		}

		Player* pPlayer = nullptr;

		auto pGameObjectList = pSceneEle->FirstChildElement("GameObjectList");

		for (TiXmlElement* pObjectEle = pGameObjectList->FirstChildElement(); pObjectEle != nullptr; pObjectEle = pObjectEle->NextSiblingElement()){

			int type = atoi(pObjectEle->Attribute("type"));

			int x = atoi(pObjectEle->Attribute("x"));

			int y = atoi(pObjectEle->Attribute("y"));

			GameObject* object = GameObjectFactory::GetInstance()->CreateObject(type);

			object->GetRect()->startPos->x = x;

			object->GetRect()->startPos->y = y;

			object->Bind(loadScene);

			if (type == MT_PLAYER){
				pPlayer = (Player*)object;
				loadScene->SetMainPlayer(pPlayer);
			}
		}

		Bag* itemBag = pPlayer->GetItemBag();

		Bag* cutBag = pPlayer->GetCutBag();

		auto pPlayerEle = pSaveFile->FirstChildElement("Player");

		int hp = atoi(pPlayerEle->Attribute("hp"));

		int coin = atoi(pPlayerEle->Attribute("coin"));

		pPlayer->SetHp(hp);

		pPlayer->SetCoin(coin);

		int weaponId = atoi(pPlayerEle->Attribute("weaponId"));

		int armorId = atoi(pPlayerEle->Attribute("armorId"));

		auto pItemBagEle = pPlayerEle->FirstChildElement("itemBag");

		for (TiXmlElement* pItemEle = pItemBagEle->FirstChildElement(); pItemEle != nullptr; pItemEle = pItemEle->NextSiblingElement()){
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
			cutBag->AddItem(Position(x, y), itemBag->findItem(itemId));
		}

		Director::GetInstance()->ReplaceScene(loadScene);
	}
}