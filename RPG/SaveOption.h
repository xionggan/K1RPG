#pragma once
#include "Marco.h"
#include "Option.h"


class SaveOption : public Option
{
public:

	SaveOption(string content, Scene* scene);

	~SaveOption();

	void SaveByMenu();

private:
	Scene* scene;
};