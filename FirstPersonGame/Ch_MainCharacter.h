#pragma once

#include <iostream>
//#include "reasings.h"             

#include "P_Collision.h"
#include "BoxCollision.h"
#include "RaycastCollision.h"

#include "AC_FirstPersonCamera.h"
#include "Gravity.h"
#include "AC_Shoot.h"

enum CharacterMovementState {
	Grounded,
	InAir,
};

class Ch_MainCharacter
{
public:

	void Start();
	void Draw();
	void Update();

	Camera& GetCamera() { return camera.GetCamera(); }
	AC_FirstPersonCamera& GetFirstPersonCam() { return camera; }

	void ProcessInputs();

	P_Collision* GetGroundCollider() { return &groundBox; }
	P_Collision* GetForwardRayRay() { return &forwardRay; }
	P_Collision* GetBodyCollider() { return &bodyBox; }

	Gravity gravity;

	CharacterMovementState state{ Grounded };


private:
	//----------COmponenets---------
	//++ToDo: vector de component parent*
	AC_FirstPersonCamera camera{};

	//----
	BoxCollision bodyBox{ Vector3{1,1.80f,1} };
	BoxCollision groundBox{Vector3{0.8,0.2f,0.8f} };

	RaycastCollision forwardRay{ {1,0,0},5.0f };

	//Créer 4 boites de collisions 
	std::uint8_t collisionDirection;
	//++ToDo: faire en sorte de bloquer quand on arrive contre les murs
	//Boite de collision orienté, besoin transform de rotation
	Ray frontRay;
	Ray backRay;
	Ray leftRay; 
	Ray rightRay;

	//----------- Transform ------------

	Vector3 pos{4,20,4};
	Vector3 forwardVector{ 1,0,0 };

	Transform transf{ {0},{0},{1,1,1} };
	//----Jump ---------
	void Jump();
	void ProcessJump();
	void StopJumping();

	float jumpVelocity = 8;
	float fallMultiplier = 2.5f;
	float lowJumpMultiplier = 2.0f;

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

	//---------For shoot ----------

	AC_Shoot shootingComponent{};



};

