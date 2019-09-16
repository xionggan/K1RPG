#pragma once

class GameObject;

class GameObjectFactory
{
public:

	static GameObjectFactory* GetInstance();

	GameObject* CreateObject(int type);

	~GameObjectFactory();

private:

	GameObjectFactory();

	static GameObjectFactory* instance;
};