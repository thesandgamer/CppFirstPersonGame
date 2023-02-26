#pragma once
#include <iostream>

#include <vector>
#include <string>

#include "raylib.h"
#include "Ch_MainCharacter.h"
#include "CollisionManager.h"
#include "CubeActor.h"
#include "Ennemy.h"


class Level
{
public:

	void Start();
	void Update();
	void Draw();
	void DrawUi();

protected:

	Ch_MainCharacter character;
	CollisionManager* CollisionManager::instance = nullptr;

	std::vector<CubeActor*> Terrain; //Stoquage des acteurs obstacles et sol
	std::vector<Ennemy*> Ennemies; //Stoquage des acteurs obstacles et sol

	CubeActor* deathzone;

};

