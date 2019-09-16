#pragma once
#include "Marco.h"

#include "Menu.h";

class Option;

class PauseMenu : public Menu
{
public:

	PauseMenu(Scene* scene ,string title, Position* _startPos, int width = 8, int height = 10);

	~PauseMenu();

	void  ResumeGame();

	virtual void AcceptKbEvent(char key);

};