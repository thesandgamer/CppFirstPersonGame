#pragma once
#include "raylib.h"
#include <set>
#include "raymath.h"
#include <iostream>

enum CollisionTouching {
	Up =1 <<0,
	Down =1 <<1,
	Front =1 <<2,
	Back = 1 << 3,
	Left = 1 << 4,
	Right =1 <<5,
};


enum CollisionLayer {
	Layer0 = 1 << 0,
	Layer1 = 1 << 1,
	Layer2 = 1 << 2,
	Layer3 = 1 << 3,
	Layer4 = 1 << 4,
	Layer5 = 1 << 5,

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
	P_Collision();
	~P_Collision();

	CollisionType collisionType{ BoxCollider };
	bool trigger{false};
	bool checkingCollision{ false };

    Vector3 GetPosition() { return Transform->translation; }

	bool IsColliding() { return collisions.size() > 0; }

	void SetParent(Transform* parentTransform) { Transform = parentTransform; }

	//std::set<std::shared_ptr<P_Collision>> collisions{};
	std::set<P_Collision*> collisions{};


	Transform Offset{ {0,0,0},{0,0,0},{1,1,1} };//Offset de transform
	//std::shared_ptr<Transform> Transform{};	//Transform du parent
	Transform* Transform{};	//Transform du parent

	virtual void Test() {};

	CollisionLayer layer{Layer0};
	CollisionLayer collideWithLayer{Layer0};



};

