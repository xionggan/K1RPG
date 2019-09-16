#include "Unity.h"


Dialog::Dialog( Position* _startPos)
:Window("¶Ô»°¿ò", _startPos, 40, 5)
{
	curIndex = 0;
	content = vector<string>();
	npc = nullptr;
}

Dialog::~Dialog()
{
	
}

void Dialog::AddContent(string _content){
	content.push_back(_content);
}

void Dialog::ClearContent(){
	content.clear();
}


void Dialog::Display(){
	DrawBorder();

	for (size_t i = 1; i < GetHeight() - 1; i++)
	{
		for (size_t j = 1; j < GetWidth() - 1; j++)
		{
			GotoXY((GetStartPos()->x + j) * 2, GetStartPos()->y + i);
			printf("  ");
		}
	}

	GotoXY(4,27);

	printf("%s",content[curIndex].data());
}

void Dialog::AcceptKbEvent(char key){
	switch (key)
	{
	case 'j':
		if (curIndex < content.size() - 1){
			curIndex += 1;
		}
		else{
			UnBind();
			curIndex = 0;
			if (npc != nullptr){
				npc->TalkFinish();
			}
		}
		break;
	default:
		return;
	}
	Display();
}