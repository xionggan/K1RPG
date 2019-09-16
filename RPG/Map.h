#pragma once
#include "Marco.h"
#include "GameLib.h"
#include <stdlib.h>
#include <vector>
using namespace std;

class GameObject;

class Map
{
public:
	Map(char* _pFlag, int maxRow, int maxCol);
	~Map();
	void SetDataValue(int x,int y,MapDataType type);
	void Display();
	void AddGameObjcet(GameObject* gameObject);
private:
	int** ppMapData;
	_SYSTEM_PRIVATE(char*, Flag, pFlag);
	_SYSTEM_PRIVATE(int, MaxRow, maxRow);
	_SYSTEM_PRIVATE(int, MaxCol, maxCol);
	_SYSTEM_PRIVATE(vector<GameObject*>, GameObjects, gameObjects);
};