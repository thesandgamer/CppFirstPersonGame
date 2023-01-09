#include "BoxCollision.h"

BoxCollision::BoxCollision()
{
}

BoxCollision::BoxCollision(Vector3 sizeP) : P_Collision()
{
	Offset.scale = sizeP;
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
	return  { Vector3{ (Transform->translation.x + Offset.translation.x) - (Transform->scale.x * Offset.scale.x / 2) ,
						(Transform->translation.y + Offset.translation.y) - (Transform->scale.y * Offset.scale.y / 2 ),
						(Transform->translation.z + Offset.translation.z) - (Transform->scale.z * Offset.scale.z / 2 )},
			Vector3{(Transform->translation.x +Offset.translation.x) + (Transform->scale.x * Offset.scale.x / 2 ) ,
					(Transform->translation.y + Offset.translation.y) + (Transform->scale.y * Offset.scale.y / 2 ) ,
					(Transform->translation.z + Offset.translation.z) + (Transform->scale.z * Offset.scale.z / 2 ) } };;
}
