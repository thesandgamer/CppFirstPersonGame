#pragma once

#include "P_Collision.h"
#include "BoxCollision.h"
#include "AC_FirstPersonCamera.h"
#include "Gravity.h"
#include <iostream>
//#include "reasings.h"                // Required for easing functions

class Ch_MainCharacter
{
public:

	void Start();
	void Draw();
	void Update();

	Camera& GetCamera() { return camera.GetCamera(); }

	void ProcessInputs();

	P_Collision* GetGroundCollider() { return &groundBox; }
	P_Collision* GetBodyCollider() { return &bodyBox; }

private:
	//----------COmponenets---------
	//++ToDo: vector de component parent*
	AC_FirstPersonCamera camera{};
	Gravity gravity;

	//----
	BoxCollision bodyBox{ &pos,Vector3{1,1.80f,1} };
	BoxCollision groundBox{ &pos,Vector3{0.8,0.2f,0.8f} };

	//Créer 4 boites de collisions 
	std::uint8_t collisionDirection;
	//++ToDo: faire en sorte de bloquer quand on arrive contre les murs
	//Boite de collision orienté, besoin transform de rotation
	Ray frontRay;
	Ray backRay;
	Ray leftRay;
	Ray rightRay;

	//----------- Transform ------------

	//++ToDo: rajouter une matrice de transform pour avoir location/rotation/scale
	Vector3 pos{4,20,4};
	Vector3 forwardVector{ 1,0,0 };

	Transform transf{};
	//----Jump ---------
	//++ToDo: state machine saut, marche,...
	void Jump();
	void StopJumping();

	bool inJump;
	//-----For movement
	void Move();

	void BaseMovement(float xValue, float yValue);
	void AccelerationFrictionMove(float xValue, float yValue);
	void MoveWithEasing(float xValue, float yValue);

	bool dir[4]{0,0,0,0};

	float actualSpeed{0};
	float maxSpeed{1};
	float acceleration{0};
	float deceleration{0};

	Vector2 acc{ 0,0 };
	Vector2 vel{ 0,0 };



};

