#pragma once
#include "raylib.h"

#define GRAVITY_VALUE 9.807

class Gravity
{
public:
	void Update();

	void SetPos(Vector3* posRefP) { refPos = posRefP; }

	bool canFall{ true };


private:
	Vector3* refPos{nullptr};

	void Fall();



	float acc{ 0 };
	float vel{ 0 };
};

