#pragma once
#include "P_Collision.h"
#include "BoxCollision.h"
#include "RaycastCollision.h"
#include <vector>

#include <iostream>
#include <string>  

class CollisionManager
{
public:
	void Start();
	void Update();
	void Draw();

	void AddCollider(P_Collision* collider) { colliders.push_back(collider); }


private:
	std::vector<P_Collision*> colliders;

	void ProcessColisions();

	void DoCollisionBoxsCheck(BoxCollision* colliderToCheck);
	void DoRayBoxCollisionCheck(RaycastCollision* colliderToCheck);

	//++ToDo faire une fonction pour check uniquement les collider proche les uns des autres

};

