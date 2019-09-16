#pragma once

class PlayerInfoUI : public Window
{
public:

	PlayerInfoUI(Player* player,Position* _startPos);

	~PlayerInfoUI();

public:

	virtual void Display();

private:

	_SYSTEM_PRIVATE_(Player*,Player,player);

};