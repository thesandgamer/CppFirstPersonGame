#pragma once
#include "Projectile.h"
#include <vector>
#include <iostream>

class AC_Shoot
{
public:
	AC_Shoot();
	~AC_Shoot();
	AC_Shoot(float cooldown);
	AC_Shoot(float cooldown, CollisionLayer layerToProjectileCollide= Layer2);

	void Start();
	void Update();
	void Draw();

	void Shoot(Vector3 position,Vector3 direction, float force = 1);


private:
	float shootSpeed{ 1 };
	float currentCooldown{ 0 };
	bool  canShoot{true};
	

	std::vector<std::unique_ptr<Projectile>> projectiles;

	bool timer{ false };
	void StartTimer();

	CollisionLayer layer{Layer1};
	CollisionLayer projectileCollideWith{Layer0};

};

