#include "Gravity.h"

void Gravity::Update()
{
	if (canFall) Fall();
	else
	{
		acc = { 0 }; 
		vel = 0;
	}

	if (Velocity.x != 0 || Velocity.y != 0 || Velocity.z != 0) 
		ProcessVelocity();
}

void Gravity::Fall()
{
	//++ToDo: gravité de chute libre sans air résistance https://en.wikipedia.org/wiki/Free_fall
	float dt = GetFrameTime();

	acc = GRAVITY_VALUE ;

	refPos->y += gravityDirection.y * ((dt * vel) + (0.5f * acc * dt * dt));
	refPos->x += gravityDirection.x * ((dt * vel) + (0.5f * acc * dt * dt));
	refPos->z += gravityDirection.z * ((dt * vel) + (0.5f * acc * dt * dt));

	vel += dt * acc;

	//DrawText(TextFormat("Vel: %02.02f ", gravityDirection.y * ((dt * vel) + (0.5f * acc * dt * dt))), 200, 220, 20, BLACK);
	//DrawText(TextFormat("Vel: %02.02f ", vel), 200, 220, 20, BLACK);

	acc = {0};
}

void Gravity::InvertGravity()
{
	gravityDirection.x *= -1;
	gravityDirection.y *= -1;
	gravityDirection.z *= -1;
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
