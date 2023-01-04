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
		if (colliderToCheck == collider) return;
		bool collide = CheckCollisionBoxes(colliderToCheck->GetBoundingBox(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
		colliderToCheck->isColliding = collide;
		collider->isColliding = collide;
		DrawText(std::to_string(collide).c_str(), 10, 10, 20, WHITE);
	
	}
}
