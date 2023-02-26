#pragma once
#include "Gravity.h"
#include "BoxCollision.h"	
#include "CubeActor.h"	

//++ToDo: rempalcer par Sphere collision
//++ToDo: D�truit quand touche : remplacer pointeurs par smart pointers



class Projectile
{
public:
	Projectile(Vector3 position, Vector3 launchForce, CollisionLayer layer = Layer2);
	~Projectile();

	void Start();
	void Draw();
	void Update();

	Gravity grav{};

	std::shared_ptr<BoxCollision> GetCollider() { return std::make_shared<BoxCollision>(collider); }

	void AddForce(Vector3 force);

private:
	BoxCollision collider{ Vector3{1,1,1} };

	Transform transform{ {0,0,0},{ 0,0,0,0},{0.2f,0.2f,0.2f} };

};

