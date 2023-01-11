#pragma once
#include "Projectile.h"
#include <vector>

class AC_Shoot
{
public:


	void Start();
	void Update();
	void Draw();

	void Shoot(Vector3 position,Vector3 direction);


private:
	float shootSpeed{ 1 };
	float currentCooldown{ 0 };
	bool  canShoot{true};
	

	std::vector<Projectile*> projectiles;

	bool timer{ false };
	void StartTimer();


};

