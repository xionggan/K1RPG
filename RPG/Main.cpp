#include "Unity.h"
#include<fstream>
#pragma comment(lib,"WINMM.LIB")

void main()
{
	srand(time(0));
	HiddenCursor();
	system("mode con cols=120 lines=40");
	SetConsoleTitleA("坦克大冒险");

	Director* pDirector = Director::GetInstance();
	pDirector->InitScene(new StartMenu);
	pDirector->GameLoop();
}
