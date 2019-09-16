#include "Unity.h"


ItemObject::ItemObject(Item* _item, Position* _position, int _width, int _height, int _type) : Walkable(_position, _width, _height, _type)
{
	SetFontColor(14);
	GetPicture()[0] = _item->GetThumbnail();
	this->item = _item;
}

ItemObject::~ItemObject()
{

}


void ItemObject::Update()
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
		player->GetItemBag()->AddItem(item);

		this->Recycle();
	}
}
