#include "Projectile.h"

#include "CollisionManager.h"

Projectile::Projectile(Vector3 position, Vector3 launchForce)
{
	transform.translation = position;
	Start();
	AddForce(launchForce);
}

Projectile::~Projectile()
{
	//delete &collider;
}

void Projectile::Start()
{
	grav.SetPos(&transform.translation);

	collider.SetParent(&transform);
	collider.checkingCollision = true;
}

void Projectile::Draw()
{
	DrawCube(transform.translation, transform.scale.x, transform.scale.y, transform.scale.z, WHITE);
	collider.Draw();
}

void Projectile::Update()
{
	grav.Update();

	//if (collider.IsColliding()) delete this;
}

void Projectile::AddForce(Vector3 force)
{
	grav.velocity = force;
}
