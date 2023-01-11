#include "P_Collision.h"

#include "CollisionManager.h"

P_Collision::P_Collision()
{
	CollisionManager::GetInstance()->AddCollider(this);//Rajoute tout seul la boite de collisoon au manager à la création
}

P_Collision::~P_Collision()
{
	CollisionManager::GetInstance()->RemoveCollider(this);//On enlève le pointeur de la liste des colliders
	collisions.clear();
	Transform = nullptr;
}
