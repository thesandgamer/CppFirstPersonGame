#include "AC_Shoot.h"


void AC_Shoot::Start()
{
}

void AC_Shoot::Update()
{
	for each (Projectile * projectile in projectiles)
	{
		projectile->Update();
	}
}

void AC_Shoot::Draw()
{
	for each (Projectile* projectile in projectiles)
	{
		projectile->Draw();
	}
}


void AC_Shoot::Shoot(Vector3 position, Vector3 direction)
{
	projectiles.emplace_back(new Projectile(position,direction));
}
