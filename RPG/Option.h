#pragma once
#include "Marco.h"


class Option
{
public:

	typedef function< void() > OptionCallBack;

	Option(string content ){
		this->content = content;
	}

	~Option(){

	}
	
	OptionCallBack optionCallBack;

private:

	_SYSTEM_PRIVATE_(string, Content, content);
};