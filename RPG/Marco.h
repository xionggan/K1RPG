#pragma once
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Tool.h"
#include "MapData.h";


using namespace std;

#define _RELEASE_SAFE_(p) if( p != nullptr ){ delete p; p = nullptr; }
#define _RELEASE_ARRAY_SAFE_(p) if( p != nullptr ){ delete[] p; p = nullptr; }

#define _SYSTEM_PRIVATE_( type, Func, value )\
public: type Get##Func(){ return value; }\
public: void Set##Func(type _value){ value = _value; }\
private: type value;


#define _SYSTEM_PRIVATE_READONLY_( type, Func, value )\
public: type Get##Func(){ return value; }\
private: type value;

#define CC_CALLBACK(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)



//函数定义：
//0 黑 1深蓝 2绿 3浅蓝 4红 5紫 6黄 7白 8灰 9中蓝  
//10亮绿 11亮蓝 12亮红 13亮紫 14亮黄 15亮灰   (7,0)-->白字黑底

void SetColor(unsigned short ForeColor, unsigned short BackGroundColor);

//调用方法：
//SetColor(7, 0);

//注意：需要头文件 #include <windows.h>


void GotoXY(int x, int y);

//隐藏光标
void HiddenCursor();

string int2str(const int &int_temp);

int str2int(const string &string_temp);