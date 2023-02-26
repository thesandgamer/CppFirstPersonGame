#pragma once
#include "Level0.h"
#include "LevelTest.h"

class LevelManager
{
public:

	void Init();

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	void GoToNextLevel();

	void ResetLevel();

private:

	int levelIndex = 0;

	std::vector<Level*> levels;




};

