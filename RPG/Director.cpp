#include "Frame.h"

Director* Director::pDirector = nullptr;

Director::Director()
{
	pSceneCur = nullptr;

	pSceneLast = nullptr;

	loop = true;
}

Director::~Director()
{

}

void Director::ReplaceScene(Scene* _pScene)
{
	if (pSceneCur != nullptr)
	{
		pSceneLast = pSceneCur;
	}

	pSceneCur = _pScene;
}

void Director::InitScene(Scene* _pScene)
{
	pSceneCur = _pScene;

	pSceneCur->Init();
}

void Director::GameLoop()
{
	while (loop)
	{ 
		pSceneCur->LogicLoop(); 

		if (pSceneLast != nullptr){
			pSceneLast->Save(); 
			delete pSceneLast;
			system("cls");
			pSceneLast = nullptr; 
			pSceneCur->Init(); 
			pSceneCur->Load(); 
		}

		pSceneCur->Display(); 
	}
}
