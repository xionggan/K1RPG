#include"Unity.h"

Item::Item(){
	id = -1;
	pFlag = "";
	describe = pFlag;
}

Item::Item(int _id,string _pFlag)
{
	id = _id;
	pFlag = _pFlag;
	describe = pFlag;
	SetThumbnail("��");
}

Item::~Item()
{

}

void Item::Effect(Player* player){

}
