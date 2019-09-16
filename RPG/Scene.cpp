#include "Frame.h"
#include "Player.h"
#include "Window.h"

Scene::Scene(int _id,char* _title, Position* _startPos, int _maxX, int _maxY, int _viewWidth, int _viewHeight)
:Window(_title, _startPos, _viewWidth + 2, _viewHeight + 2)
{
	pGameObjectList = new list<GameObject*>();

	pWindowList = new vector<Window*>();

	maxX = _maxX;
	maxY = _maxY;

	ppMapData = new MapData**[_maxX];

	for (size_t i = 0; i < _maxX; i++)
	{
		ppMapData[i] = new MapData*[_maxY];
	}

	for (size_t i = 0; i < _maxX; i++)
	{
		for (size_t j = 0; j < _maxY; j++)
		{
			ppMapData[i][j] = nullptr;
		}
	}

	viewWidth = 40;
	viewHeight = 30;
	viewRange = -1;

	infoUI = nullptr;
	cutUI = nullptr;
	id = _id;
}


Scene::~Scene()
{
	auto begin = pGameObjectList->begin();

	while (begin != pGameObjectList->end()){
		_RELEASE_SAFE_(*begin);
		begin++;
	}

	pGameObjectList->clear();

	_RELEASE_SAFE_(pGameObjectList);

	for (size_t i = 0; i < maxX; i++)
	{
		_RELEASE_ARRAY_SAFE_(ppMapData[i]);
	}

	_RELEASE_ARRAY_SAFE_(ppMapData);

}

void Scene::Init()
{

}

void Scene::LogicLoop()
{
	// -----  清空  ---------

	auto iBegin = pGameObjectList->begin();

	while (iBegin != pGameObjectList->end())
	{
		(*iBegin)->ClearObject();

		iBegin++;
	}


	// ----- 逻辑更新  ------

	iBegin = pGameObjectList->begin();

	while (iBegin != pGameObjectList->end())
	{
		(*iBegin)->Update();

		iBegin++;
	}

	// ------ 延迟回收
	iBegin = pGameObjectList->begin();

	while (iBegin != pGameObjectList->end())
	{
		if ((*iBegin)->GetRecycle())
		{
			delete *iBegin;
			iBegin = pGameObjectList->erase(iBegin);
			continue;
		}

		iBegin++;
	}

	// ------ 绘制 ------

	iBegin = pGameObjectList->begin();

	while (iBegin != pGameObjectList->end())
	{
		(*iBegin)->DrawObject();

		iBegin++;
	}
}


void Scene::Display()
{
	int maxX = GetMaxX();
	int maxY = GetMaxY();

	MapData*** ppMapData = GetMapData();
	GameObject* player = GetMainPlayer();

	int playerX = player->GetRect()->startPos->x;
	int playerY = player->GetRect()->startPos->y;

	int startMapX = playerX - viewWidth / 2;
	int startMapY = playerY - viewHeight / 2;

	for (size_t j = GetStartPos()->y + 1; j < GetStartPos()->y + 1 + viewHeight; j++)
	{
		for (size_t i = GetStartPos()->x + 1; i < GetStartPos()->x + 1 + viewWidth; i++)
		{

			bool needDraw = true;
			for (size_t k = 0; k < pWindowList->size(); k ++)
			{
				if ((*pWindowList)[k]->GetRect()->isContain(i,j)){
					needDraw = false;
					break;
				}
			}
			
			if (!needDraw){
				continue;
			}

			GotoXY(i * 2, j);
			if (startMapX + i < 0 || startMapY + j < 0 || startMapX + i >= maxX || startMapY + j >= maxY){
				SetColor(15, 0);
				printf("  ");
				continue;
			}

			MapData* mapData = ppMapData[startMapX + i][startMapY + j];

			if (mapData != nullptr)
			{
				GameObject* object = mapData->object;
				Position* selfPos = mapData->pos;
				Position worldPos = Position(object->GetRect()->startPos->x + selfPos->x, object->GetRect()->startPos->y + selfPos->y);

				if (viewRange>0)
				{
					if (object->GetVisiable() && player->GetRect()->getCenterPos()->GetDistance(worldPos) < viewRange)
					{
						string* picture = object->GetPicture();
						SetColor(object->GetFontColor(), object->GetBgColor());
						printf("%s", picture[selfPos->y].substr(selfPos->x * 2, 2).data());
					}
					else
					{
						SetColor(15, 0);
						printf("  ");
					}
				}
				else
				{
					if (object->GetVisiable())
					{
						string* picture = object->GetPicture();
						SetColor(object->GetFontColor(), object->GetBgColor());
						printf("%s", picture[selfPos->y].substr(selfPos->x * 2, 2).data());
					}
					else
					{
						SetColor(15, 0);
						printf("  ");
					}
				}
			}
			else
			{
				SetColor(15, 0);
				printf("  ");
			}
		}
	}

	//for (size_t i = 0; i < pWindowList->size(); i++)
	//{
	//	(*pWindowList)[i]->Display();
	//}

	SetColor(15, 0);
}

