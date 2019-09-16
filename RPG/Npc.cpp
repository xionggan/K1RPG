#include "Unity.h"

Npc::Npc(Position* _position, int _width , int _height , int _type )
: Block(_position, _width, _height, _type)
{
	SetFontColor(11);
	SetBgColor(0);
	GetPicture()[0] = "●__●";

	menu = new Menu("--",new Position(20,15));

	Option* option = new Option("交谈");

	option->optionCallBack = CC_CALLBACK(Npc::Talk, this);

	menu->AddOption(option);

	option = new Option("商店");

	option->optionCallBack = CC_CALLBACK(Npc::Shopping, this);

	menu->AddOption(option);

	shop = new Shop("商店",new Position(1,1));

	shop->init();

	dialog = new Dialog(new Position(1,25));

	dialog->SetNpc(this);

	ChangeStatus(NS_WAITTASK);

	triggerRect = new Rect(new Position(0,0), 5, 3);

	playerCurKillCount = 0;

}

Npc::~Npc()
{
	delete(triggerRect);
	delete(shop);
}

void Npc::ChangeStatus(NpcStatus status){
	dialog->ClearContent();
	switch (status)
	{
	case NS_WAITTASK:
		dialog->AddContent("冷漠的商人:小伙子，这里是表情怪泛滥的世界。");

		dialog->AddContent("冷漠的商人:像你和我这样一脸正经的人已经很少见了。");

		dialog->AddContent("冷漠的商人:我讨厌表情怪，你先帮我杀两个表情怪，我可以给你个好东西");
		break;
	case NS_INTASK:

		dialog->AddContent("冷漠的商人:快点去杀掉那些表情怪吧，我已经烦的不行了。");

		break;
	case NS_FINISHTASK:

		dialog->AddContent("冷漠的商人:很好，看来你很有能力，这把加农炮就送给你了。");

		dialog->AddContent("冷漠的商人:我还帮你开启了去表情怪老巢的传送门,");

		dialog->AddContent("冷漠的商人:你进去后会遇到他们的老大，干掉他，世界就能恢复平静了。");

		dialog->AddContent("冷漠的商人:你也可以继续打怪找我买更多的装备。");

		dialog->AddContent("冷漠的商人:,要小心，他很强大，要做好万全的准备。");

		break;

	case NS_NORMAL:

		dialog->AddContent("冷漠的商人:小伙子,看好你哦。");

		break;
	default:
		break;
	}

	this->status = status;

}

void Npc::Talk(){

	menu->UnBind();

	if (status == NS_INTASK){
		Player* player = (Player*)GetScene()->GetMainPlayer();

		if (player->GetKillCount() - playerCurKillCount >= 2){
			ChangeStatus(NS_FINISHTASK);
			player->GetItemBag()->AddItem(ItemFactory::GetInstance()->CreateItem(IT_CANNON));
			((HillyLand*)GetScene())->RandomAddGameObject(MT_GATEWAY, 1);
		}
	}

	dialog->Bind(GetScene());
}

void Npc::TalkFinish(){
	if (status == NS_WAITTASK){

		Player* player = (Player*)GetScene()->GetMainPlayer();

		playerCurKillCount = player->GetKillCount();

		ChangeStatus(NS_INTASK);
	}
	else if (status == NS_FINISHTASK){
		ChangeStatus(NS_NORMAL);
	}
}


void Npc::Shopping(){
	menu->UnBind();
	shop->Bind(GetScene());
}

void Npc::Update(){

	if (GetKeyState('K') & 0x8000){

		triggerRect->startPos->x = GetRect()->startPos->x - 1;

		triggerRect->startPos->y = GetRect()->startPos->y - 1;

		GameObject* playerObject = GetScene()->GetMainPlayer();

		if (playerObject == nullptr){
			return;
		}

		Player* player = dynamic_cast<Player*>(playerObject);

		if (player == NULL){
			return;
		}

		if (triggerRect->isIntersect(player->GetRect()))
		{
			menu->Bind(GetScene());
		}
	}
}