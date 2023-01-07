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

	if (Velocity.x != 0 || Velocity.y != 0 || Velocity.z != 0) 
		ProcessVelocity();
}

void Gravity::Fall()
{
	//++ToDo: gravité de chute libre sans air résistance https://en.wikipedia.org/wiki/Free_fall
	float dt = GetFrameTime();

	if (canFall)
		velocity.y -= GRAVITY_VALUE * dt;
	else
		velocity.y = 0;

	refPos->y += ((dt * velocity.y) + (0.5f * GRAVITY_VALUE * dt * dt));

	std::cout << "Vel: " << velocity.x<<" "<< velocity.y<<" "<< velocity.z << "\n";

}


void Gravity::ProcessVelocity()
{
	float dt = GetFrameTime();

	v_acc = 1;

	refPos->y += Velocity.y * ((dt * v_vel) + (0.5f * v_acc * dt * dt));
	refPos->x += Velocity.x * ((dt * v_vel) + (0.5f * v_acc * dt * dt));
	refPos->z += Velocity.z * ((dt * v_vel) + (0.5f * v_acc * dt * dt));

	v_vel += dt * v_acc;

	v_acc = { 0 };
}
