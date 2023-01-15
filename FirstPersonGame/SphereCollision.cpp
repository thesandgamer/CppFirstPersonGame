#include "SphereCollision.h"

SphereCollision::SphereCollision()
{
}

SphereCollision::SphereCollision(float radius) : P_Collision()
{
    rad = radius;
}

void SphereCollision::Draw()
{
    DrawSphere(GetCollider().Center, GetCollider().Radius, (IsColliding()) ? RED : GREEN);
}

Sphere SphereCollision::GetCollider()
{
    return { {Transform->translation.x + Offset.translation.x,
          Transform->translation.y + Offset.translation.y,
          Transform->translation.z + Offset.translation.z },
        rad
    };
}
