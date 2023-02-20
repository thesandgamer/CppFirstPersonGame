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

	collider.collideWithLayer = Layer3;	//Collideavec le alyer 3 = body du player
	collider.layer = Layer2;	//La sphere de détéction est sur la layer2
	collider.checkingCollision = true;

	collider.id = 8;
}

Ennemy::~Ennemy()
{
}

void Ennemy::Start()
{
	shootComponenet.Start();
}

void Ennemy::Draw()
{
	shootComponenet.Draw();
	DrawSphere(transform.translation, 2, RED);
	collider.Draw();
}

void Ennemy::Update()
{
	shootComponenet.Update();
	if (collider.IsColliding())
	{
		//++ToDo: si il y a une collision, il va prendre le focus sur le premier acteur à être rentré	
		//Si il peut lui tirer dessus il va lui lancer un projectile
		P_Collision* tar = *(collider.collisions.begin());
		target = tar->Transform;
		//std::cout << "last collide: " << (*(collider.collisions.end()))->layer << std::endl;

	}
	else
	{
		//target = nullptr;
	}

	if (target) Shoot();//SI peut tirer et à une target tire

}

void Ennemy::Shoot()
{
	if (target == nullptr)
	{
		std::cout << "Ennemy have no target" << std::endl; 
		return;
	}

	Vector3 direction{0,0,0};
	//Look at: where target, vector up
	Vector3 v = { (target->translation.x - transform.translation.x),
		(target->translation.y - transform.translation.y),
	(target->translation.z - transform.translation.z) };
	float unit = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	direction = {
		(1 / unit) * v.x,
		(1 / unit) * v.y,
		(1 / unit) * v.z,
	};

	shootComponenet.Shoot(transform.translation, {direction.x*10,direction.y*10,direction.z*10});//++ToDo: faire en sorte que la direction soit vers la target
}

void Ennemy::ReloadShoot()
{
}
