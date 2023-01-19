#include "Gravity.h"

void Gravity::Update()
{
	Fall();
}

void Gravity::Fall()
{
	float dt = GetFrameTime();

	//-----Gravité
	if (canFall)
		velocity.y -= GRAVITY_VALUE * dt;
	else
		velocity.y = 0;

	Vector3 nextPos = {
			refPos->x + ((dt * velocity.x) + (0.5f * acceleration * dt * dt)),
			refPos->y + ((dt * velocity.y) + (0.5f * GRAVITY_VALUE * dt * dt)),
			refPos->z + ((dt * velocity.z) + (0.5f * acceleration * dt * dt))
	};

	if (AnticipateCollisions::NextMoveIsColliding(colliderToCheckForCollisions, nextPos)) return;

	refPos->y += ((dt * velocity.y) + (0.5f * GRAVITY_VALUE * dt * dt));

	//++ToDo: refacto pour que ça fasse un truc qui marche vraiment bien
	refPos->x += ((dt * velocity.x) + (0.5f * acceleration * dt * dt));
	refPos->z += ((dt * velocity.z) + (0.5f * acceleration * dt * dt));

	//std::cout << "Vel: " << velocity.x<<" "<< velocity.y<<" "<< velocity.z << "\n";

}


