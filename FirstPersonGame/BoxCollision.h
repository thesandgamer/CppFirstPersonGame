#pragma once
#include "P_Collision.h"


//++ToDo faire un parent compoenent avec une fonction vrtuelle de start draw update
class BoxCollision :
    public P_Collision
{
public:
	BoxCollision();
	BoxCollision(Vector3* posP, Vector3 sizeP);
	~BoxCollision();

	void Draw();

	BoundingBox GetBoundingBox(); //++Todo Renvoyer un pointeur de bounding box

	Vector3 GetPosition() { return *pos; };



private:
	Vector3* pos{nullptr};
	Vector3 size{ -1 };


	//++ToDo trouver un moyen de créer une box avec comme param une pointeur vers une valeur
};


