#pragma once
#include "Frame.h"

class DrakPrairie : public Scene
{
public:

	DrakPrairie();

	~DrakPrairie();

	void RandomAddGameObject(MapType type, int count);

public:

	virtual void Init();

	virtual void Display();

	virtual void Load();

};
