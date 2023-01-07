#pragma once
#include "P_Collision.h"


//++ToDo faire un parent compoenent avec une fonction virtuelle de start draw update


class BoxCollision :
    public P_Collision
{
public:
	BoxCollision();
	BoxCollision(Vector3 sizeP);
	~BoxCollision();

	void Draw();

	BoundingBox GetBoundingBox(); //++Todo Renvoyer un pointeur de bounding box

	void Test() {};


private:


	//++ToDo trouver un moyen de créer une box avec comme param une pointeur vers une valeur
};


