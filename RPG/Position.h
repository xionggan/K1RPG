#pragma once

struct Position
{
	Position(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}

	int x;
	int y;

	bool operator<(const Position& _dest) const
	{
		if (this->x < _dest.x)
		{
			return true;
		}
		else if (this->x > _dest.x)
		{
			return false;
		}
		
		return this->y >= _dest.y ? false : true;
	}

	Position operator+(const Position& _dest) const
	{
		return Position(this->x + _dest.x, this->y + _dest.y);
	}

	Position operator-(const Position& _dest) const
	{
		return Position(this->x - _dest.x, this->y - _dest.y);
	}

	int GetDistance(Position _dest){
		int xDistance = abs(this->x - _dest.x);
		int yDistance = abs(this->y - _dest.y);
		return sqrt(xDistance*xDistance + yDistance*yDistance);
	}

	bool operator==(const Position& _dest) const
	{
		return this->x == _dest.x && this->y == _dest.y ? true : false;
	}  
};
