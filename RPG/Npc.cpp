#include "Unity.h"

Npc::Npc(Position* _position, int _width , int _height , int _type )
: Block(_position, _width, _height, _type)
{
	SetFontColor(11);
	SetBgColor(0);
	GetPicture()[0] = "��__��";

	menu = new Menu("--",new Position(20,15));

	Option* option = new Option("��̸");

	option->optionCallBack = CC_CALLBACK(Npc::Talk, this);

	menu->AddOption(option);

	option = new Option("�̵�");

	option->optionCallBack = CC_CALLBACK(Npc::Shopping, this);

	menu->AddOption(option);

	shop = new Shop("�̵�",new Position(1,1));

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
		dialog->AddContent("��Į������:С���ӣ������Ǳ���ַ��ĵ����硣");

		dialog->AddContent("��Į������:�����������һ�����������Ѿ����ټ��ˡ�");

		dialog->AddContent("��Į������:���������֣����Ȱ���ɱ��������֣��ҿ��Ը�����ö���");
		break;
	case NS_INTASK:

		dialog->AddContent("��Į������:���ȥɱ����Щ����ְɣ����Ѿ����Ĳ����ˡ�");

		break;
	case NS_FINISHTASK:

		dialog->AddContent("��Į������:�ܺã������������������Ѽ�ũ�ھ��͸����ˡ�");

		dialog->AddContent("��Į������:�һ����㿪����ȥ������ϳ��Ĵ�����,");

		dialog->AddContent("��Į������:���ȥ����������ǵ��ϴ󣬸ɵ�����������ָܻ�ƽ���ˡ�");

		dialog->AddContent("��Į������:��Ҳ���Լ����������������װ����");

		dialog->AddContent("��Į������:,ҪС�ģ�����ǿ��Ҫ������ȫ��׼����");

		break;

	case NS_NORMAL:

		dialog->AddContent("��Į������:С����,������Ŷ��");

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