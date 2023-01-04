#pragma once
#include "raylib.h"


enum CollisionType {
	BoxCollider,
	SphereCollider,
	MeshCollider,
};

class P_Collision
{
public:
	CollisionType collisionType{ BoxCollider };
	bool trigger{false};
	virtual Vector3 GetPosition();

	bool isColliding{ false };


	//++ToDo rajouter un offset pour décaler la boite de collision

};

