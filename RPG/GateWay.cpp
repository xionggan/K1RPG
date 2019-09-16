#include "Unity.h"


GateWay::GateWay(Position* _position, int width, int height, int type) : Walkable(_position, width, height, type)
{
	SetFontColor(14);
	GetPicture()[0] = "©³©¥©·";
	GetPicture()[1] = "©§  ©§";
	GetPicture()[2] = "©»©¥©¿";
}

GateWay::~GateWay()
{

}


void GateWay::Update()
{
	GameObject* playerObject = GetScene()->GetMainPlayer();

	if (playerObject == nullptr){
		return;
	}

	Player* player = dynamic_cast<Player*>(playerObject);

	if (player == NULL){
		return;
	}

	if (this->GetRect()->isIntersect(player->GetRect()))
	{
		Director::GetInstance()->ReplaceScene(new DrakPrairie);
	}
}
