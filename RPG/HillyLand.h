#pragma once
#include "Frame.h"

class HillyLand	: public Scene
{
public:

	HillyLand();

	~HillyLand();

	void RandomAddGameObject(MapType type, int count);

	void SaveByMenu();

public:

	virtual void Init();

	virtual void Display();

	virtual void Save();

};
