#pragma once
class GameObject;
struct Position;

struct MapData
{
public:

	MapData(GameObject* _object,Position* _pos){
		this->object = _object;
		this->pos = _pos;
	}

	~MapData(){
		if (pos != nullptr){
			delete(pos);
			pos = nullptr;
		}
	}

	GameObject* object;
	//��������ϵλ��
	Position* pos;

};