#include "CollisionManager.h"

void CollisionManager::Start()
{
}

void CollisionManager::Update()
{
	ProcessColisions();
}

void CollisionManager::Draw()
{
}

void CollisionManager::ProcessColisions()
{
	for each (P_Collision * collider in colliders)
	{
		if (!collider->checkingCollision)continue;
		switch (collider->collisionType)
		{
		case BoxCollider:
			DoCollisionBoxsCheck(dynamic_cast<BoxCollision*>(collider));
		break;

		default:
			break;
		}
	}
}

void CollisionManager::DoCollisionBoxsCheck(BoxCollision* colliderToCheck)
{
	for each (P_Collision* collider in colliders)
	{
		if (colliderToCheck == collider) continue;
		bool collide = CheckCollisionBoxes(colliderToCheck->GetBoundingBox(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
		if (collide)
		{
			colliderToCheck->collisions.insert(collider);
			collider->collisions.insert(colliderToCheck);
		}
		else
		{
			colliderToCheck->collisions.erase(collider);
			collider->collisions.erase(colliderToCheck);

		}
	
	}
}
