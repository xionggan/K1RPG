#include "Unity.h"


PlayerInfoUI::PlayerInfoUI(Player* player,Position* _startPos)
:Window("��ɫ��Ϣ", _startPos, 15, 32)
{
	this->player = player;
}

PlayerInfoUI::~PlayerInfoUI()
{
}

void PlayerInfoUI::Display(){
	DrawBorder();
	SetColor(14, 0);
	Position* pos = GetStartPos();
	GotoXY((pos->x + 1)*2, pos->y + 1);
	printf("Ѫ����");
	for (size_t i = 0; i < player->GetMaxHp() / 10; i++)
	{
		printf("��");
	}
	GotoXY((pos->x + 4)*2, pos->y + 1);
	for (size_t i = 0; i < player->GetHp() / 10; i++)
	{
		printf("��");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 3);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 3);

	if (player->GetWeapon() != nullptr){
		printf("����:%s", player->GetWeapon()->GetFlag().data());
	}
	else{
		printf("����:%s", "��ũ��");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 5);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 5);

	if (player->GetArmor() != nullptr){
		printf("װ��:%s", player->GetArmor()->GetFlag().data());
	}
	else {
		printf("װ��:%s", "����װ��");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 7);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 7);

	printf("������:%d", player->GetAtk());

	GotoXY((pos->x + 1) * 2, pos->y + 9);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 9);

	printf("������:%d", player->GetDef());

	GotoXY((pos->x + 1) * 2, pos->y + 11);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 11);

	if (player->GetWeapon() != nullptr && (player->GetWeapon()->GetId() == IT_WALLBUILDER || player->GetWeapon()->GetId() == IT_DRILL))
	{
		printf("ʯ����:%d", player->GetItemBag()->findItemCount(IT_STONE));
	}
	else{
		printf("�ӵ���:%d", player->GetItemBag()->findItemCount(IT_AMMO));
	}

	GotoXY((pos->x + 1) * 2, pos->y + 13);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 13);
	printf("�����:%d", player->GetCoin());

	GotoXY((pos->x + 1) * 2, pos->y + 14);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("--");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 15);
	printf("������ʾ:");
	GotoXY((pos->x + 1) * 2, pos->y + 17);
	printf("�ƶ�:w,a,s,d");
	GotoXY((pos->x + 1) * 2, pos->y + 19);
	printf("����������ʹ�õ���:j");
	GotoXY((pos->x + 1) * 2, pos->y + 21);
	printf("NPC����:k");
	GotoXY((pos->x + 1) * 2, pos->y + 23);
	printf("�˳�����:l");
	GotoXY((pos->x + 1) * 2, pos->y + 25);
	printf("��/�رձ���:c");
	GotoXY((pos->x + 1) * 2, pos->y + 27);
	printf("���õ������:x");
	GotoXY((pos->x + 1) * 2, pos->y + 29);
	printf("�����:1,2,3,4,5");
}