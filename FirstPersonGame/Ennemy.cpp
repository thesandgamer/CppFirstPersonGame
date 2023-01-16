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
	shootCOmponenet.Start();
}

void Ennemy::Draw()
{
	shootCOmponenet.Draw();
	DrawSphere(transform.translation, 2, RED);
	collider.Draw();
}

void Ennemy::Update()
{
	shootCOmponenet.Update();
	if (collider.IsColliding())
	{
		//++ToDo: si il y a une collision, il va prendre le focus sur le premier acteur à être rentré	
		//Si il peut lui tirer dessus il va lui lancer un projectile
		P_Collision* tar = *(collider.collisions.begin());
		target = tar->Transform;

	}
	else
	{
		target = nullptr;
	}

	if (target) Shoot();//SI peut tirer et à une target tire

}

void Ennemy::Shoot()
{
	shootCOmponenet.Shoot(transform.translation, { 0,0,0 });//++ToDo: faire en sorte que la direction soit vers la target
}

void Ennemy::ReloadShoot()
{
}
