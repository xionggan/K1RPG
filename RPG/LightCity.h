#pragma once
#include "Frame.h"
class PlayerInfoUI;
class ShortcutBag;

class LightCity	: public Scene
{
public:

	LightCity();
	~LightCity();

public:

	virtual void Init();

	void RandomAddGameObject(MapType type, int count);

	virtual void Display();

private:
	_SYSTEM_PRIVATE_(PlayerInfoUI*, InfoUI, infoUI);
	_SYSTEM_PRIVATE_(ShortcutBag*, CutUI, cutUI);
};
