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



//�������壺
//0 �� 1���� 2�� 3ǳ�� 4�� 5�� 6�� 7�� 8�� 9����  
//10���� 11���� 12���� 13���� 14���� 15����   (7,0)-->���ֺڵ�

void SetColor(unsigned short ForeColor, unsigned short BackGroundColor);

//���÷�����
//SetColor(7, 0);

//ע�⣺��Ҫͷ�ļ� #include <windows.h>


void GotoXY(int x, int y);

//���ع��
void HiddenCursor();

string int2str(const int &int_temp);

int str2int(const string &string_temp);