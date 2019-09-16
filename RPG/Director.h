#pragma once

class Scene;

class Director
{
public:

	~Director();

public:

	// --- 核心函数 --
	// 作用: 切换场景
	// 参数 Scene* _pScene  新的场景
	void ReplaceScene(Scene* _pScene);

	// ---- 核心函数 ---
	// 作用: -- 初始化第一个场景 --
	// 参数 Scene* _pScene  新的场景
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
