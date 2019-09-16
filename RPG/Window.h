#pragma once
#include "Marco.h"
class Scene;
struct Position;

class Window
{
public:
	Window(string title, Position* _startPos, int width = 100, int height = 100);

	~Window();

	int GetContentWidth();

	int GetContentHeight();

	void Dismiss();

	void Bind(Scene* _pScene);

	void UnBind();

public: 

	virtual void DrawBorder();

	virtual void Display() = 0;

	virtual void AcceptKbEvent(char key);

private:

	_SYSTEM_PRIVATE_(string, Title, title);
	_SYSTEM_PRIVATE_(Position*, StartPos, startPos);
	_SYSTEM_PRIVATE_(int, Width, width);
	_SYSTEM_PRIVATE_(int, Height, height);
	_SYSTEM_PRIVATE_(int, BorderColor, borderColor);
	_SYSTEM_PRIVATE_READONLY_(bool, Binding, isBinding);
	_SYSTEM_PRIVATE_READONLY_(Scene*, Scene, pScene);
	_SYSTEM_PRIVATE_(Rect*, Rect, rect);
};
