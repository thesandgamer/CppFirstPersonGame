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

	void Start();
	void Update();
	void Draw();

	void Shoot(Vector3 position,Vector3 direction);


private:
	float shootSpeed{ 1 };
	float currentCooldown{ 0 };
	bool  canShoot{true};
	

	std::vector<std::unique_ptr<Projectile>> projectiles;

	bool timer{ false };
	void StartTimer();


};

