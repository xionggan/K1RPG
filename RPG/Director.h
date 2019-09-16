#pragma once

class Scene;

class Director
{
public:

	~Director();

public:

	// --- ���ĺ��� --
	// ����: �л�����
	// ���� Scene* _pScene  �µĳ���
	void ReplaceScene(Scene* _pScene);

	// ---- ���ĺ��� ---
	// ����: -- ��ʼ����һ������ --
	// ���� Scene* _pScene  �µĳ���
	void InitScene(Scene* _pScene);

	void GameLoop();

	static Director* GetInstance()
	{
		if (pDirector == nullptr)
		{
			pDirector = new Director();
		}

		return pDirector;
	}

private:

	Director();

	Scene* pSceneCur;

	Scene* pSceneLast;

	static Director* pDirector;

	_SYSTEM_PRIVATE_(bool, Loop, loop);

};
