#pragma once
#include "Bag.h"

class ShortcutBag : public Bag
{
public:

	ShortcutBag(Player* owner, Position* startPos);

	~ShortcutBag();

public:

	virtual void AcceptKbEvent(char key);

private:

	_SYSTEM_PRIVATE_(Player*, Player, player);


};
