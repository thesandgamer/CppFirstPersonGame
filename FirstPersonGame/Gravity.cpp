#include "Gravity.h"

void Gravity::Update()
{
	Fall();
	/*
	if (!canFall) 
	{
		velocity.y = 0;
		//std::cout << "Vel: " << vel << "\n";
	}*/

}

void Gravity::Fall()
{
	float dt = GetFrameTime();

	if (canFall)
		velocity.y -= GRAVITY_VALUE * dt;
	else
		velocity.y = 0;

	refPos->y += ((dt * velocity.y) + (0.5f * GRAVITY_VALUE * dt * dt));

	//++ToDo: refacto pour que �a fasse un truc qui marche vraiment bien
	refPos->x += ((dt * velocity.x) + (0.5f * acceleration * dt * dt));
	refPos->z += ((dt * velocity.z) + (0.5f * acceleration * dt * dt));

	//std::cout << "Vel: " << velocity.x<<" "<< velocity.y<<" "<< velocity.z << "\n";

}


