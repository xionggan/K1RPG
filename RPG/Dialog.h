#pragma once
#include "Marco.h"
class Npc;

class Dialog : public Window
{
public:

	Dialog(Position* _startPos);

	~Dialog();

	void AddContent(string content);

	void ClearContent();

public:

	virtual void Display();

	virtual void AcceptKbEvent(char key);

private:

	vector<string> content;

	int curIndex;

	_SYSTEM_PRIVATE_(Npc*, Npc, npc);

};