#include "Unity.h"

BackTitleOption::BackTitleOption(string content)
:Option(content)
{
	optionCallBack = CC_CALLBACK(BackTitleOption::BackTitle, this);
}

BackTitleOption::~BackTitleOption(){

}

void BackTitleOption::BackTitle(){
	Director::GetInstance()->ReplaceScene(new StartMenu);
}