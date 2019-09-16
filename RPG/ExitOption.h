#pragma once
#include "Marco.h"
#include "Option.h"


class ExitOption : public Option
{
public:

	ExitOption(string content);

	~ExitOption();

	void Exit();

};