#include "Unity.h"


Menu::Menu(string title,Position* _startPos, int width, int height)
:Window(title, _startPos, width, height)
{
	curIndex = 0;
	options = vector<Option*>();
	canCanle = true;
	isDrawBorder = true;
}

Menu::~Menu()
{
	auto begin = options.begin();
	while (begin != options.end()){
		delete(*begin);
		begin++;
	}
	options.clear();
}


void Menu::AddOption(Option* option){
	options.push_back(option);
}

void Menu::Display(){

	if (isDrawBorder == true){
		DrawBorder();
	}

	int contentStartX = GetStartPos()->x + 1;

	int contentStartY = GetStartPos()->y + 1;

	int size = options.size();


	for (size_t i = 1; i < GetHeight() - 1; i++)
	{
		for (size_t j = 1; j < GetWidth() - 1; j++)
		{
			GotoXY((GetStartPos()->x + j) * 2, GetStartPos()->y + i);
			printf("  ");
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		GotoXY((contentStartX) * 2, contentStartY + i * 2 );

		for (size_t j = 1; j < GetWidth() - 1; j++)
		{
			printf("  ");
		}

		if (curIndex == i){
			SetColor(GetBorderColor(), 8);
		}

		GotoXY(contentStartX * 2, contentStartY + i * 2 + 1);

		Option* temp = options[i];

		int spaceLength = (GetWidth() - 2 - temp->GetContent().length()/2) / 2;

		for (size_t i = 0; i < spaceLength; i++)
		{
			printf("  ");
		}

		printf("%s", temp->GetContent().data());

		for (size_t i = 0; i < spaceLength; i++)
		{
			printf("  ");
		}

		SetColor(GetBorderColor(), 0);

	}
}

void  Menu::AcceptKbEvent(char key){
	switch (key)
	{
	case 'w':
		if (curIndex > 0){
			curIndex -= 1;
		}
		break;

	case 's':
		if (curIndex < options.size() - 1){
			curIndex += 1;
		}
		break;

	case 'j':
		options[curIndex]->optionCallBack();
		break;

	case 'l':
		if (canCanle){
			UnBind();
		}
		break;
	default:
		return;
	}
	Display();
}