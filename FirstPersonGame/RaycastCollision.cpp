#include "RaycastCollision.h"

RaycastCollision::RaycastCollision()
{
    collisionType = RayCollider;
}

RaycastCollision::RaycastCollision(Vector3 directionP,float lengthP): direction(directionP), length{lengthP}
{
    collisionType = RayCollider;
}

RaycastCollision::~RaycastCollision()
{
}

void RaycastCollision::Draw()
{
    DrawRay(GetRay(),length, (IsColliding()) ? RED : GREEN);
}

Ray RaycastCollision::GetRay()
{
    return {Vector3Add( Transform->translation, Offset.translation),direction };
}
