#pragma once
#include "Level0.h"
#include "LevelTest.h"
#include "Level01.h"

class LevelManager
{
	//--------------Make it a singleton------------------
private:
	LevelManager() {};
	static LevelManager* instance;

public:
	LevelManager(const LevelManager& obj) = delete;
	void operator=(const LevelManager&) = delete;

	static LevelManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new LevelManager();
		}
		return instance;
	}


public:

	void Init();

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	void GoToNextLevel();

	void ResetLevel();

private:

	int levelIndex{ 0 };

	std::vector<Level*> levels;




};

