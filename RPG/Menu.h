#pragma once
#include "Marco.h"

class Option;

class Menu : public Window
{
public:

	Menu(string title,Position* _startPos,int width = 6 ,int height = 8);

	~Menu();

	void AddOption(Option* option);

public:

	virtual void Display();

	virtual void AcceptKbEvent(char key);

private:

	_SYSTEM_PRIVATE_(vector<Option*>, Options , options);

	_SYSTEM_PRIVATE_(int, CurIndex, curIndex);

	_SYSTEM_PRIVATE_(bool, CanCanle,canCanle);
	
	_SYSTEM_PRIVATE_(bool, IsDrawBorder, isDrawBorder);
};