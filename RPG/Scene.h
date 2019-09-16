#pragma once
#include "Marco.h"
#include "Window.h"
class PlayerInfoUI;
class ShortcutBag;


class GameObject;

class Scene : public Window
{
public:

	Scene(int id,char* title, Position* displayStartPos, int maxX, int maxY, int viewWidth = 40, int viewHeight = 30);
	
	~Scene();

public:

	virtual void Init();

	virtual void Display();

	virtual void Save(){}

	virtual void Load(){}

public:

	void LogicLoop();

	template< typename T >
	list<T>* FindGameObjectsByTag()
	{
		list<T>* pList = new list<T>;

		auto iBegin = pGameObjectList->begin();

		while (iBegin != pGameObjectList->end())
		{
			T t = dynamic_cast<T>(*iBegin);

			if (t != nullptr)
			{
				pList->push_back(t);
			}

			iBegin++;
		}

		return pList;
	}

private:

	_SYSTEM_PRIVATE_( list<GameObject*>*, GameObjectList, pGameObjectList );
	_SYSTEM_PRIVATE_READONLY_( vector<Window*>*, WindowList, pWindowList);
	_SYSTEM_PRIVATE_(int, MaxX, maxX);
	_SYSTEM_PRIVATE_(int, MaxY, maxY);
	_SYSTEM_PRIVATE_(GameObject*, MainPlayer, mainPlayer);
	_SYSTEM_PRIVATE_(MapData***, MapData, ppMapData);
	_SYSTEM_PRIVATE_(int, ViewWidth, viewWidth);
	_SYSTEM_PRIVATE_(int, ViewHeight, viewHeight);
	_SYSTEM_PRIVATE_(int, ViewRange, viewRange);
	_SYSTEM_PRIVATE_(PlayerInfoUI*, InfoUI, infoUI);
	_SYSTEM_PRIVATE_(ShortcutBag*, CutUI, cutUI);
	_SYSTEM_PRIVATE_(int, Id, id);
};
