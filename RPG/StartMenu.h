#pragma once
#include "Frame.h"
class StartMenu : public Scene
{
public:

	StartMenu();

	~StartMenu();

	void RandomAddGameObject(MapType type, int count);

public:

	virtual void Init();

	virtual void Display();

private:

	Menu* menu;

	void StartGame();

	void ExitGame();

};
