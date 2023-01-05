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
	DrawBoundingBox(GetBoundingBox(), (IsColliding()) ? RED : GREEN);
}

BoundingBox BoxCollision::GetBoundingBox()
{
	return  { Vector3{ pos->x - size.x / 2 + Offset.x, 
						pos->y - size.y / 2 + Offset.y,
						pos->z - size.z / 2 + Offset.z},
			Vector3{pos->x + size.x / 2 + Offset.x,
					pos->y + size.y / 2 + Offset.y,
					pos->z + size.z / 2 + Offset.z} };;
}
