#include "Unity.h"



ShortcutBag::ShortcutBag(Player* owner, Position* startPos)
:Bag(owner, startPos, 5, 1, false,"ÎäÆ÷À¸")
{
}

ShortcutBag::~ShortcutBag()
{

}


void ShortcutBag::AcceptKbEvent(char key){
	Position curPos = GetCurPos();
	curPos.x;
	switch (key)
	{
	case '1':
		curPos.x = 0;
		break;
	case '2':
		curPos.x = 1;
		break;
	case '3':
		curPos.x = 2;
		break;
	case '4':
		curPos.x = 3;
		break;
	case '5':
		curPos.x = 4;
		break;
	default:
		return;
	}
	SetCurPos(curPos);
	UseItem();
	Display();
}