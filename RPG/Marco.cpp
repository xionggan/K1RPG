#include "Marco.h"
#include <sstream>

//0 黑 1深蓝 2绿 3浅蓝 4红 5紫 6黄 7白 8灰 9中蓝  
//10亮绿 11亮蓝 12亮红 13亮紫 14亮黄 15亮灰   (15,0)-->白字黑底
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
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
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