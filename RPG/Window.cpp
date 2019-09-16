#include "Unity.h"

Window::Window(string _title,Position* _startPos, int _width , int _height)
{
	title = _title;
	startPos = _startPos;
	if (_width < title.length() + 2){
		width = title.length() + 2;
	}
	else{
		width = _width;
	}
	height = _height;

	borderColor = 14;

	isBinding = false;

	rect = new Rect(_startPos, _width, _height);

	//DrawBorder();
}

Window::~Window()
{

}

int Window::GetContentWidth(){
	return width - 2;
}

int Window::GetContentHeight(){
	return height - 2;
}


void Window::DrawBorder(){
	SetColor(borderColor,0);
	GotoXY(startPos->x * 2, startPos->y);
	int titleLen = title.length()/2;
	int titleLeftLen = 0;
	int titleRightLen = 0;
	if ((width - 2 - titleLen) % 2 == 0){
		titleLeftLen = titleRightLen = (width - 2 - titleLen) / 2;
	}
	else{
		titleLeftLen = (width - 2 - titleLen) / 2;
		titleRightLen = titleLeftLen + 1;
	}
	printf("©°");
	for (size_t i = 0; i < titleLeftLen; i++)
	{
		printf("--");
	}
	printf("%s",title.data());
	for (size_t i = 0; i < titleRightLen; i++)
	{
		printf("--");
	}
	printf("©´");
	for (size_t i = 1; i < height - 1; i++)
	{
		GotoXY(startPos->x * 2, startPos->y + i);
		printf("©¦");
		GotoXY((startPos->x + width - 1) * 2, startPos->y + i);
		printf("©¦");
	}

	GotoXY(startPos->x * 2, startPos->y + height - 1);
	printf("©¸");
	for (size_t i = 0; i < width - 2; i++)
	{
		printf("--");
	}
	printf("©¼");
}

void Window::AcceptKbEvent(char key){
	Display();
}

void Window::Bind(Scene* _pScene)
{
	if (!isBinding){
		this->pScene = _pScene;

		auto windowList = _pScene->GetWindowList();

		windowList->push_back(this);

		isBinding = true;
	}
	Display();
}

void Window::UnBind()
{
	if (isBinding){
		pScene->GetWindowList()->pop_back();
		isBinding = false;
	}

}