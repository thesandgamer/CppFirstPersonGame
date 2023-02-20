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


void AC_Shoot::Shoot(Vector3 position, Vector3 direction, float force)
{
	if (canShoot)
	{
		/*
		Projectile newProjectile = Projectile(position, { direction.x * force,direction.y * force ,direction.z * force });
		newProjectile.GetCollider().get()->collideWithLayer = projectileCollideWith;//Pour faire que ça collide avec le body du player*/
		canShoot = false;
		projectiles.emplace_back(new Projectile(position, { direction.x * force,direction.y * force ,direction.z * force }));
		//projectiles.back().get()->GetCollider().get()->collideWithLayer = projectileCollideWith;
		StartTimer();
	}
}

void AC_Shoot::StartTimer()
{
	timer = true;
	currentCooldown = shootSpeed;
}
