#pragma once
#include "Marco.h"

class Scene;

class GameObject
{
public:

	GameObject(Position* _position, int width = 1, int height = 1, int type = -1);

	~GameObject();

public:

	virtual void Update();

	void Recycle();

	void DrawObject();

	void ClearObject();


public:

	void Bind(Scene* _pScene);

private:

	_SYSTEM_PRIVATE_(bool, Recycle, bRecycle);

	_SYSTEM_PRIVATE_READONLY_(Scene*, Scene, pScene);

	_SYSTEM_PRIVATE_(bool, Visiable, visiable);

	_SYSTEM_PRIVATE_(Rect*, Rect, rect);

	_SYSTEM_PRIVATE_(string*, Picture, picture);

	_SYSTEM_PRIVATE_(int, FontColor, fontColor);

	_SYSTEM_PRIVATE_(int, BgColor, bgColor);

	_SYSTEM_PRIVATE_(int, Type, type);
};

