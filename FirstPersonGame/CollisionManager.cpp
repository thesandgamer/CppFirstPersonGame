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
	for each (P_Collision* collider in colliders) //On va récupérer un collider et regarder si il collide avec les autres collider
	{
		if (!collider->checkingCollision)continue;
		//++ToDo: checker si les deux collider ont le même parent, ou si l'un est parent de l'autre, et avoir un bool pour savoir si on veut désactiver les collisons entre eux
		switch (collider->collisionType)
		{
		case BoxCollider:
			DoCollisionBoxsCheck(dynamic_cast<BoxCollision*>(collider));
		break;

		case RayCollider:
			DoRayBoxCollisionCheck(dynamic_cast<RaycastCollision*>(collider));
		break;

		case SphereCollider:

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
		if (colliderToCheck->collideWithLayer != collider->layer) continue;
		bool collide = false;
		switch (collider->collisionType)
		{
		case BoxCollider:
			collide = CheckCollisionBoxes(colliderToCheck->GetBoundingBox(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
			break;
		case RayCollider:
			RayHitInfo hitinfo = GetRayCollisionBox(dynamic_cast<RaycastCollision*>(collider)->GetRay(), colliderToCheck->GetBoundingBox());
			collide = hitinfo.hit && hitinfo.distance <= dynamic_cast<RaycastCollision*>(collider)->GetLength();
			break;
		case SphereCollider:
			collide = CheckCollisionBoxSphere(colliderToCheck->GetBoundingBox(),
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center, dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius);
			break;
		default:
			break;
		}
		InsertCollision(collide, collider, colliderToCheck);

	
	
	}
}

void CollisionManager::DoRayBoxCollisionCheck(RaycastCollision* colliderToCheck)
{
	for each (P_Collision * collider in colliders)
	{
		if (colliderToCheck == collider) continue;
		if (colliderToCheck->collideWithLayer != collider->layer) continue;
		bool collide = false;

		switch (collider->collisionType)
		{
		case BoxCollider:
			RayHitInfo hitinfo = GetRayCollisionBox(colliderToCheck->GetRay(), dynamic_cast<BoxCollision*>(collider)->GetBoundingBox());
			collide = hitinfo.hit && hitinfo.distance <= dynamic_cast<RaycastCollision*>(collider)->GetLength();
			break;

		case SphereCollider:
			RayHitInfo hit = GetRayCollisionSphere(colliderToCheck->GetRay(), 
				dynamic_cast<SphereCollision*>(collider)->GetCollider().Center, dynamic_cast<SphereCollision*>(collider)->GetCollider().Radius);
			collide = hit.hit && hit.distance <= dynamic_cast<RaycastCollision*>(collider)->GetLength();
			break;

		}		
		InsertCollision(collide, collider, colliderToCheck);

	}
}

void CollisionManager::DoSphereBoxCollisionCheck(SphereCollision* colliderToCheck)
{
}

void CollisionManager::InsertCollision(bool insert, P_Collision* collider, P_Collision* colliderToCheck)
{
	if (insert)
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


