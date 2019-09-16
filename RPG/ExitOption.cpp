#include "Unity.h"

ExitOption::ExitOption(string content)
:Option(content)
{
	optionCallBack = CC_CALLBACK(ExitOption::Exit, this);
}

ExitOption::~ExitOption(){

}

void ExitOption::Exit(){
	Director::GetInstance()->SetLoop(false);
	GotoXY(0, 32);
	exit(0);
}