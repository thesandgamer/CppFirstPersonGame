#pragma once
#include "BoxCollision.h"

class CubeActor
{
public:
	CubeActor();
	CubeActor(Vector3 posP,Vector3 sizeP,Color colorP);
	~CubeActor();

	void Start();
	void Draw();
	void Update();

	Vector3* GetPos() { return &pos; }
	Vector3* GetSize() { return &size; }

	BoxCollision* GetCollision() { return &collision; }

private:
	Vector3 pos{0,0,0};
	Vector3 size{1,1,1};
	BoxCollision collision{&pos,size};
	Color color{ PURPLE };
};

