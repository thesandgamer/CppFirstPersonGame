#include "P_Collision.h"

#include "CollisionManager.h"

P_Collision::P_Collision()
{
	CollisionManager::GetInstance()->AddCollider(this);//Rajoute tout seul la boite de collisoon au manager � la cr�ation
}

P_Collision::~P_Collision()
{
	CollisionManager::GetInstance()->RemoveCollider(this);//On enl�ve le pointeur de la liste des colliders
	collisions.clear();
	Transform = nullptr;
}
