#include "CubeActor.h"

CubeActor::CubeActor()
{
}

CubeActor::CubeActor(Vector3 posP, Vector3 sizeP,Color colorP): pos{posP},size{sizeP}, color(colorP)
{
}

CubeActor::~CubeActor()
{
}

void CubeActor::Start()
{
}

void CubeActor::Draw()
{
	DrawCube(pos, size.x, size.y, size.z, color);
	collision.Draw();

}

void CubeActor::Update()
{
}
