#include "BoxCollision.h"

BoxCollision::BoxCollision()
{
}

BoxCollision::BoxCollision(Vector3* posP, Vector3 sizeP) : pos{ posP }, size{ sizeP }
{
	
}

BoxCollision::~BoxCollision()
{
}

void BoxCollision::Draw()
{
	DrawBoundingBox(GetBoundingBox(), (isColliding) ? RED : GREEN );
}

BoundingBox BoxCollision::GetBoundingBox()
{
	return  { Vector3{ pos->x - size.x / 2, pos->y - size.y / 2, pos->z - size.z / 2 },
		Vector3{pos->x + size.x / 2,pos->y + size.y / 2,pos->z + size.z / 2} };;
}
