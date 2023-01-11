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

void CollisionManager::RemoveCollider(P_Collision* colliderToRemove)
{
	colliders.erase(std::find(colliders.begin(), colliders.end(), colliderToRemove));
	
}

void CollisionManager::ProcessColisions()
{
	for each (P_Collision* collider in colliders) //On va r�cup�rer un collider et regarder si il collide avec les autres collider
	{
		if (!collider->checkingCollision)continue;
		//++ToDo: checker si les deux collider ont le m�me parent, ou si l'un est parent de l'autre, et avoir un bool pour savoir si on veut d�sactiver les collisons entre eux
		switch (collider->collisionType)
		{
		case BoxCollider:
			DoCollisionBoxsCheck(dynamic_cast<BoxCollision*>(collider));
		break;

		case RayCollider:
			DoRayBoxCollisionCheck(dynamic_cast<RaycastCollision*>(collider));
		break;

		default:
			break;
		}
	}
}

/// <summary>
/// On check les collisions entre des BB et d'autres BB
/// </summary>
/// <param name="colliderToCheck"></param>
void CollisionManager::DoCollisionBoxsCheck(BoxCollision* colliderToCheck)
{
	for each (P_Collision* collider in colliders)
	{
		if (colliderToCheck == collider) continue;
		if (collider->collisionType != BoxCollider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;

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

void CollisionManager::DoRayBoxCollisionCheck(RaycastCollision* colliderToCheck)
{
	for each (P_Collision * collider in colliders)
	{
		if (colliderToCheck == collider) continue;
		if (collider->collisionType != BoxCollider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;
		
		RayHitInfo collide = GetRayCollisionBox(colliderToCheck->GetRay(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
		if (collide.hit && collide.distance <= colliderToCheck->GetLength())
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
