#pragma once
#include "Level.h"
#include "Level0.h"

class LevelManager
{
public:

	void Init();

	void Start();
	void Update();
	void Draw();
	void DrawUi();

	void GoToNextLevel();

private:

	int levelIndex = 1;

	std::vector<Level*> levels;


};

