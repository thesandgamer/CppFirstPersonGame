#pragma once

#include "P_Collision.h"
#include "BoxCollision.h"
#include "AC_FirstPersonCamera.h"
#include "Gravity.h"
//#include "reasings.h"                // Required for easing functions

class Ch_MainCharacter
{
public:

	void Start();
	void Draw();
	void Update();

	Camera& GetCamera() { return camera.GetCamera(); }

	void ProcessInputs();

	BoxCollision collisionBox {&pos,Vector3{1,2,1} };

private:
	//----------COmponenets---------
	AC_FirstPersonCamera camera{};
	Gravity gravity;
	//-----------

	Vector3 pos{4,20,4};
	Vector3 forwardVector{ 1,0,0 };

	//---
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

