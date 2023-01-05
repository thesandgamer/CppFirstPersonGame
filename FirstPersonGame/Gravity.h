#pragma once
#include "raylib.h"
#include "raymath.h"

#define GRAVITY_VALUE 9.807

class Gravity
{
public:
	void Update();

	void SetPos(Vector3* posRefP) { refPos = posRefP; }

	bool canFall{ true };

	void InvertGravity();

	Vector3 Velocity{ 0,0,0 };


private:
	Vector3* refPos{nullptr};

	void Fall();

	Vector3 gravityDirection{0,-1,0};

	float acc{ 0 };
	float vel{ 0 };

	//------------
	void ProcessVelocity();

	float v_acc{ 0 };
	float v_vel{ 0 };
};

