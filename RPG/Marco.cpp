#include "Marco.h"
#include <sstream>

//0 �� 1���� 2�� 3ǳ�� 4�� 5�� 6�� 7�� 8�� 9����  
//10���� 11���� 12���� 13���� 14���� 15����   (15,0)-->���ֺڵ�
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}


void GotoXY(int x, int y){
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void HiddenCursor(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

string int2str(const int &int_temp)
{
	string string_temp;
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();
	return string_temp;
}

int str2int(const string &string_temp)
{
	int int_temp = 0;
	stringstream stream(string_temp);
	stream >> int_temp;
	return int_temp;
}