#include "LevelManager.h"

void LevelManager::Init()
{
	levels.emplace_back(Level0());
}

void LevelManager::Start()
{
	levels.at(levelIndex)->Start();
}

void LevelManager::Update()
{
	levels.at(levelIndex)->Update();

}

void LevelManager::Draw()
{
	levels.at(levelIndex)->Draw();

}

void LevelManager::DrawUi()
{
	levels.at(levelIndex)->DrawUi();

}

void LevelManager::GoToNextLevel()
{
}
