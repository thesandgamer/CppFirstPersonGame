#pragma once
#include "Gravity.h"
#include "BoxCollision.h"	
#include "CubeActor.h"	

//++ToDo: projectile
//++ToDo: Sphere collision
//++ToDo: Détruit quand touche
//++ToDo: Vitesse du projectile(utiliser gravity.velocity)
//++ToDo: Il utilise la gravité et tombe

class Projectile
{
public:
	Projectile(Vector3 position, Vector3 launchForce);
	~Projectile();

	void Start();
	void Draw();
	void Update();

	Gravity grav{};

	P_Collision* GetCollider() { return &collider; }

	void AddForce(Vector3 force);

private:
	BoxCollision collider{ Vector3{1,1,1} };

	Transform transform{ {0,0,0},{ 0,0,0,0},{0.2f,0.2f,0.2f} };

};

