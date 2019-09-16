#pragma once
#include "Marco.h"
#include "Option.h"


class LoadOption : public Option
{
public:

	LoadOption(string content);

	~LoadOption();

	void LoadByMenu();

private:
	Scene* scene;
};