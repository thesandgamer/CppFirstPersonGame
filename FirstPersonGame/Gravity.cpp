#include "Gravity.h"

void Gravity::Update()
{
	if (canFall) Fall();
	else
	{
		acc = { 0 }; 
		vel = 0;
	}
}

void Gravity::Fall()
{
	float dt = GetFrameTime();

	acc += GRAVITY_VALUE ;

	refPos->y -= dt * vel + 0.5f * acc * dt * dt;

	vel += dt * acc;

	acc = {0};
}
