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
};

class P_Collision
{
public:
	CollisionType collisionType{ BoxCollider };
	bool trigger{false};
	virtual Vector3 GetPosition();

	bool IsColliding() { return collisions.size() > 0; }


	std::set<P_Collision*> collisions{};

	Vector3 Offset{0,0,0};

	//++ToDo: mettre en place le transform et le offset transform
	Matrix* transform{};//++ToDo: le transform du componenet doit est le même que celui du owner



};

