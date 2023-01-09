#pragma once
#include "raylib.h"
#include "raymath.h"

#include <iostream>

#define GRAVITY_VALUE 9.807

class Gravity
{
public:
	void Update();

	void SetPos(Vector3* posRefP) { refPos = posRefP; }

	bool canFall{ true };

	float acceleration{ 1 };
	Vector3 velocity{ 0,0,0 };

private:
	Vector3* refPos{nullptr};

	void Fall();





	
};

