#include "Ennemy.h"

Ennemy::Ennemy()
{
}

Ennemy::Ennemy(Vector3 pos, float detectionRadius)
{
	transform.translation = pos;
	collider = SphereCollision(detectionRadius);//Peut être juste avoir une fonction set radius
	collider.trigger = true; //Cette collision sera un trigger
	collider.SetParent(&transform);
	collider.collideWithLayer = Layer1;
	collider.layer = Layer2;
	collider.checkingCollision = true;
}

Ennemy::~Ennemy()
{
}

void Ennemy::Start()
{
}

void Ennemy::Draw()
{
	DrawSphere(transform.translation, 2, RED);
	collider.Draw();
}

void Ennemy::Update()
{
}
