#include "Unity.h"
#include "tinyxml\tinyxml.h"
#include<fstream>

StartMenu::StartMenu()
:Scene(0,"��ʼ�˵�", new Position(0, 0), 60, 45)
{

}

StartMenu::~StartMenu()
{
	delete(menu);
}

void StartMenu::Init()
{
	// ��ͣ
	mciSendString(TEXT("close background "), NULL, 0, NULL);
	// ���� mp3
	WCHAR mciCmd[] = TEXT("open ./Sounds/��������.mp3 alias background"); //.mp3��ʽ��
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

	Option* option = new Option("��ʼ��Ϸ");

	option->optionCallBack = CC_CALLBACK(StartMenu::StartGame, this);

	menu->AddOption(option);

	option = new LoadOption("��ȡ�浵");

	menu->AddOption(option);

	option = new Option("�˳�");

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