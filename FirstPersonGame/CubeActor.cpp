#include "CubeActor.h"

CubeActor::CubeActor()
{
}

CubeActor::CubeActor(Vector3 posP, Vector3 sizeP,Color colorP): color(colorP)
{
	transform.translation = posP;
	transform.scale = sizeP;

	collision.SetParent(&transform);

}

CubeActor::~CubeActor()
{
}

void CubeActor::Start()
{
}

void CubeActor::Draw()
{
	DrawCube(transform.translation, transform.scale.x, transform.scale.y, transform.scale.z, color);
	collision.Draw();

}

void CubeActor::Update()
{
}
