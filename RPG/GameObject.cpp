#include "Frame.h"

GameObject::GameObject(Position* _position, int _width, int _height,int _type )
{
	rect = new Rect(_position, _width, _height);

	bRecycle = false;

	visiable = true;

	picture = new string[_height];

	for (size_t i = 0; i < _height; i++)
	{
		picture[i] = new char[_width];
	}

	for (size_t i = 0; i < _height; i++)
	{
		for (size_t j = 0; j < _width; j++)
		{
			picture[i][j] = NULL;
		}
	}

	fontColor = 15;

	bgColor = 0;

	type = _type;

}

GameObject::~GameObject()
{
	_RELEASE_SAFE_(rect);

	_RELEASE_ARRAY_SAFE_(picture);

}

void GameObject::Recycle()
{
	// -- 必须延迟回收 --
	bRecycle = true;
}

void GameObject::Bind(Scene* _pScene)
{
	this->pScene = _pScene;

	// ---- ☆☆☆ （ 天坑、程序会崩的 ）----
	auto gameObjectList = _pScene->GetGameObjectList();

	gameObjectList->push_back(this);
}

void GameObject::DrawObject()
{
	MapData*** ppMapData = this->pScene->GetMapData();

	Position* startPos = rect->startPos;

	for (size_t i = 0; i < rect->width; i++)
	{
		for (size_t j = 0; j < rect->height; j++){

			_RELEASE_SAFE_(ppMapData[startPos->x + i][startPos->y + j]);

			ppMapData[startPos->x + i][startPos->y + j] = new MapData(this, new Position(i, j));
		}
	}
}

void GameObject::ClearObject()
{
	MapData*** ppMapData = this->pScene->GetMapData();

	Position* startPos = rect->startPos;

	for (size_t i = 0; i < rect->width; i++)
	{
		for (size_t j = 0; j < rect->height; j++){
			ppMapData[startPos->x + i][startPos->y + j] = nullptr;
		}
	}
}

void GameObject::Update()
{

}