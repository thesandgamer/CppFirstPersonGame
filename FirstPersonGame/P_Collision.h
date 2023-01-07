#pragma once
#include "raylib.h"
#include <set>
#include "raymath.h"

enum CollisionTouching {
	Up =1 <<0,
	Down =1 <<1,
	Front =1 <<2,
	Back = 1 << 3,
	Left = 1 << 4,
	Right =1 <<5,
};

enum CollisionType {
	BoxCollider,
	SphereCollider,
	MeshCollider,
	RayCollider,
};

class P_Collision
{
public:
	CollisionType collisionType{ BoxCollider };
	bool trigger{false};
	bool checkingCollision{ false };

    Vector3 GetPosition() { return Transform->translation; }

	bool IsColliding() { return collisions.size() > 0; }

	void SetParent(Transform* parentTransform) { Transform = parentTransform; }

	std::set<P_Collision*> collisions{};


	Transform Offset{ {0,0,0},{0,0,0},{1,1,1} };//Offset de transform
	Transform* Transform{};	//Transform du parent

	virtual void Test() {};
	//++ToDo: mettre en place le transform et le offset transform



};

