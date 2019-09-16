#include "Unity.h"

PauseMenu::PauseMenu(Scene* scene,string title, Position* _startPos, int width , int height)
:Menu(title, _startPos, width, height)
{
	Option* option = new Option("继续游戏");

	option->optionCallBack = CC_CALLBACK(PauseMenu::ResumeGame, this);

	AddOption(option);

	option = new SaveOption("保存游戏", scene);

	AddOption(option);

	option = new BackTitleOption("返回标题");

	AddOption(option);

}

PauseMenu::~PauseMenu(){

}

void PauseMenu::ResumeGame(){
	UnBind();
}

void  PauseMenu::AcceptKbEvent(char key){

	int curIndex = GetCurIndex();

	switch (key)
	{
	case 'w':
		if (curIndex > 0){
			curIndex -= 1;
		}
		break;

	case 's':
		if (curIndex < GetOptions().size() - 1){
			curIndex += 1;
		}
		break;

	case 'j':
		if (GetOptions()[curIndex] != nullptr){
			GetOptions()[curIndex]->optionCallBack();
		}
		UnBind();
		break;

	case 'l':
		UnBind();
		break;
	default:
		return;
	}
	SetCurIndex(curIndex);
	Display();
}