#pragma once
#include "P_Collision.h"


class RaycastCollision :
    public P_Collision
{
public:
    RaycastCollision();
    RaycastCollision(Vector3 directionP, float lengthP);
    ~RaycastCollision();

    void Draw();

    Ray GetRay();

    void Test() {};

    float GetLength() { return length; }

private:
    Vector3 direction{0,0,0};
    float length;

};

