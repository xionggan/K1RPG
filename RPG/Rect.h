#pragma once
#include "Position.h"
#include <math.h>

struct Rect
{
	Rect(Position* _startPos, int width = 1, int height = 1)
	{
		this->startPos = _startPos;
		this->width = width;
		this->height = height;
	}

	Rect(const Rect& rect)
	{
		this->startPos = new Position();
		this->startPos->x = rect.startPos->x;
		this->startPos->y = rect.startPos->y;

		this->width = rect.width;
		this->height = rect.height;
	}

	~Rect(){
		if (startPos != nullptr){
			delete(startPos);
			startPos = nullptr;
		}
	}


	Position* startPos;
	int width;
	int height;

	Position* getEndPos(){
		return new Position(startPos->x + width -1,startPos->y + height -1);
	}

	Position* getCenterPos(){
		return new Position(startPos->x + width/2, startPos->y + height/2);
	}

	int GetDistance(Rect* other){
		int xDistance = abs(this->getCenterPos()->x - other->getCenterPos()->x);
		int yDistance = abs(this->getCenterPos()->y - other->getCenterPos()->y);
		return sqrt(xDistance*xDistance + yDistance*yDistance);
	}


	bool isIntersect(Rect* other)
	{
		Position* endPos = getEndPos();

		int x01 = this->startPos->x;
		int x02 = endPos->x;
		int y01 = this->startPos->y;
		int y02 = endPos->y;

		int x11 = other->startPos->x;
		int x12 = other->getEndPos()->x;
		int y11 = other->startPos->y;
		int y12 = other->getEndPos()->y;

		int zx = abs(x01 + x02 - x11 - x12);
		int x = abs(x01 - x02) + abs(x11 - x12);
		int zy = abs(y01 + y02 - y11 - y12);
		int y = abs(y01 - y02) + abs(y11 - y12);
		if (zx <= x && zy <= y)
			return 1;
		else
			return 0;
	}

	bool isContain(Rect* other)
	{
		Position* endPos = getEndPos();

		int x01 = this->startPos->x;
		int x02 = endPos->x;
		int y01 = this->startPos->y;
		int y02 = endPos->y;

		int x11 = other->startPos->x;
		int x12 = other->getEndPos()->x;
		int y11 = other->startPos->y;
		int y12 = other->getEndPos()->y;

		if ((x01 <= x11 && x02 >= x12 && y01 <= y11 && y02 >= y12) || (x11 <= x01 && x12 >= x02 && y11 <= y01 && y12 >= y02)){
			return 1;
		}
		else{
			return 0;
		}
	}

	bool isContain(int x,int y){
		if (x >= startPos->x && x < startPos->x + width && y >= startPos->y && y < startPos->y + height){
			return 1;
		}
		else{
			return 0;
		}
	}
};