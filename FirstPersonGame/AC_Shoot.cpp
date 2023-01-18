#include "AC_Shoot.h"


AC_Shoot::AC_Shoot()
{
}

AC_Shoot::~AC_Shoot()
{
}

AC_Shoot::AC_Shoot(float cooldown):shootSpeed(cooldown)
{
}

AC_Shoot::AC_Shoot(float cooldown, CollisionLayer layerToProjectileCollide) :shootSpeed(cooldown), projectileCollideWith{layerToProjectileCollide}
{

}

void AC_Shoot::Start()
{
}

void AC_Shoot::Update()
{
	//------------Pour faire qu'on puisse shoot que tout les xs
	if (timer)
	{
		currentCooldown -= GetFrameTime();
		if (currentCooldown <= 0)
		{
			timer = false;
			canShoot = true;
		}
	}
	//-----------
	for (auto i = projectiles.begin(); i != projectiles.end(); i++)
	{
		if (*i)
		{
			(*i).get()->Update();

		}
	}

}

void AC_Shoot::Draw()
{
	for (auto i = projectiles.begin(); i != projectiles.end(); i++)
	{
		if (*i)
		{
			(*i).get()->Draw();
		}
	}
}


void AC_Shoot::Shoot(Vector3 position, Vector3 direction)
{
	if (canShoot)
	{
		Projectile* newProjectile = new Projectile(position, direction);
		//newProjectile->GetCollider().get()->collideWithLayer = Layer3;//Pour faire que ça collide avec le body du player
		canShoot = false;
		projectiles.emplace_back(new Projectile(position, direction));
		StartTimer();
	}
}

void AC_Shoot::StartTimer()
{
	timer = true;
	currentCooldown = shootSpeed;
}
