#include "Unity.h"
#include "tinyxml\tinyxml.h"

SaveOption::SaveOption(string content, Scene* scene)
:Option(content)
{
	this->scene = scene;
	optionCallBack = CC_CALLBACK(SaveOption::SaveByMenu, this);
}

SaveOption::~SaveOption(){

}

void SaveOption::SaveByMenu()
{
	auto pPlayer = scene->FindGameObjectsByTag<Player*>()->front();

	TiXmlDocument doc;

	TiXmlElement* pSaveFile = new TiXmlElement("SaveFile");

	TiXmlElement* pPlayerEle = new TiXmlElement("Player");

	pPlayerEle->SetAttribute("hp", pPlayer->GetHp());

	pPlayerEle->SetAttribute("coin", pPlayer->GetCoin());

	pPlayerEle->SetAttribute("weaponId", pPlayer->GetWeapon()->GetId());

	pPlayerEle->SetAttribute("armorId", pPlayer->GetArmor() != nullptr ? pPlayer->GetArmor()->GetId() : -1);

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

	pSaveFile->LinkEndChild(pPlayerEle);

	//µØÍ¼ÔªËØ
	TiXmlElement* pScnenEle = new TiXmlElement("Scene");

	pScnenEle->SetAttribute("id", scene->GetId());

	TiXmlElement* pGameObjectListEle = new TiXmlElement("GameObjectList");

	auto objectBegin = scene->GetGameObjectList()->begin();

	while (objectBegin != scene->GetGameObjectList()->end()){

		GameObject* tempObject = *objectBegin;

		if (tempObject->GetType() == MT_BULLET || tempObject->GetType() == MT_ITEM){
			objectBegin++;
			continue;
		}

		TiXmlElement* pObjectEle = new TiXmlElement("GameObject");

		pObjectEle->SetAttribute("type", tempObject->GetType());

		pObjectEle->SetAttribute("x", tempObject->GetRect()->startPos->x);

		pObjectEle->SetAttribute("y", tempObject->GetRect()->startPos->y);

		pGameObjectListEle->LinkEndChild(pObjectEle);

		objectBegin++;
	}

	pScnenEle->LinkEndChild(pGameObjectListEle);

	pSaveFile->LinkEndChild(pScnenEle);

	doc.LinkEndChild(pSaveFile);

	doc.SaveFile("File/Player/SaveFile.xml");
}