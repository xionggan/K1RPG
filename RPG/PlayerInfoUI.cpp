#include "Unity.h"


PlayerInfoUI::PlayerInfoUI(Player* player,Position* _startPos)
:Window("角色信息", _startPos, 15, 32)
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
	printf("血量：");
	for (size_t i = 0; i < player->GetMaxHp() / 10; i++)
	{
		printf("☆");
	}
	GotoXY((pos->x + 4)*2, pos->y + 1);
	for (size_t i = 0; i < player->GetHp() / 10; i++)
	{
		printf("★");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 3);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 3);

	if (player->GetWeapon() != nullptr){
		printf("武器:%s", player->GetWeapon()->GetFlag().data());
	}
	else{
		printf("武器:%s", "加农炮");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 5);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 5);

	if (player->GetArmor() != nullptr){
		printf("装甲:%s", player->GetArmor()->GetFlag().data());
	}
	else {
		printf("装甲:%s", "常规装甲");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 7);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 7);

	printf("攻击力:%d", player->GetAtk());

	GotoXY((pos->x + 1) * 2, pos->y + 9);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 9);

	printf("防御力:%d", player->GetDef());

	GotoXY((pos->x + 1) * 2, pos->y + 11);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 11);

	if (player->GetWeapon() != nullptr && (player->GetWeapon()->GetId() == IT_WALLBUILDER || player->GetWeapon()->GetId() == IT_DRILL))
	{
		printf("石材数:%d", player->GetItemBag()->findItemCount(IT_STONE));
	}
	else{
		printf("子弹数:%d", player->GetItemBag()->findItemCount(IT_AMMO));
	}

	GotoXY((pos->x + 1) * 2, pos->y + 13);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("  ");
	}
	GotoXY((pos->x + 1) * 2, pos->y + 13);
	printf("金币数:%d", player->GetCoin());

	GotoXY((pos->x + 1) * 2, pos->y + 14);
	for (size_t i = 1; i < GetWidth() - 1; i++)
	{
		printf("--");
	}

	GotoXY((pos->x + 1) * 2, pos->y + 15);
	printf("操作提示:");
	GotoXY((pos->x + 1) * 2, pos->y + 17);
	printf("移动:w,a,s,d");
	GotoXY((pos->x + 1) * 2, pos->y + 19);
	printf("攻击、购买、使用道具:j");
	GotoXY((pos->x + 1) * 2, pos->y + 21);
	printf("NPC交互:k");
	GotoXY((pos->x + 1) * 2, pos->y + 23);
	printf("退出交互:l");
	GotoXY((pos->x + 1) * 2, pos->y + 25);
	printf("打开/关闭背包:c");
	GotoXY((pos->x + 1) * 2, pos->y + 27);
	printf("设置到快捷栏:x");
	GotoXY((pos->x + 1) * 2, pos->y + 29);
	printf("快捷栏:1,2,3,4,5");
}