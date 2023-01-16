#pragma once
#include "SphereCollision.h"

//++ToDo: ennemi: neutre, quand quelque chose entre dans boite de collision va regarder et tirer sur ce qui rentre
class Ennemy
{
public:
	Ennemy();
	Ennemy(Vector3 pos, float detectionRadius);
	~Ennemy();


	void Start();
	void Draw();
	void Update();

	SphereCollision* GetCollider() { return &collider; }
	Vector3* GetPos() { return &transform.translation; }

	Transform transform{ {0,0,0},{0,0,0,0},{1,1,1} };

private:

	SphereCollision collider;
};

