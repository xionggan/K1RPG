#include "Unity.h"
#include "tinyxml\tinyxml.h"
#include<fstream>

StartMenu::StartMenu()
:Scene(0,"开始菜单", new Position(0, 0), 60, 45)
{

}

StartMenu::~StartMenu()
{
	delete(menu);
}

void StartMenu::Init()
{
	// 暂停
	mciSendString(TEXT("close background "), NULL, 0, NULL);
	// 音乐 mp3
	WCHAR mciCmd[] = TEXT("open ./Sounds/背景音乐.mp3 alias background"); //.mp3格式的
	mciSendString(mciCmd, NULL, 0, NULL);
	mciSendString(TEXT("play background repeat"), NULL, 0, NULL);

	char buffer[256];

	ifstream in("test.txt");

	SetColor(15, 0);

	while (!in.eof()){
		in.getline(buffer, 256);
		cout << buffer << endl;
	}

	menu = new Menu("--", new Position(20, 30), 20, 10);

	Option* option = new Option("开始游戏");

	option->optionCallBack = CC_CALLBACK(StartMenu::StartGame, this);

	menu->AddOption(option);

	option = new LoadOption("读取存档");

	menu->AddOption(option);

	option = new Option("退出");

	option->optionCallBack = CC_CALLBACK(StartMenu::ExitGame, this);

	menu->AddOption(option);

	menu->SetCanCanle(false);

	menu->SetIsDrawBorder(false);

	menu->SetBorderColor(15);

	menu->Display();

}


void StartMenu::StartGame(){
	 Director::GetInstance()->ReplaceScene(new HillyLand);
}

void StartMenu::ExitGame(){
	exit(0);
}

void StartMenu::Display(){
	menu->AcceptKbEvent(getch());
}