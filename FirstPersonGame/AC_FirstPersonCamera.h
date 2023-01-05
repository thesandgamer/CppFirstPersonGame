#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct CameraData
{
	float playerEyesPosition;       // Player eyes position from ground (in meters)
	float targetDistance;           // Camera distance from position to target
	Vector2 angle;                  // Camera angle in plane XZ

};

class AC_FirstPersonCamera
{
public:

	void Start();
	void Draw();
	void Update();

	Camera& GetCamera() { return cam; }
	void MoveCamera(Vector3 newPos);

	Vector2 GetAngle() { return camData.angle; }

private:
	//Position
	//Rotation
	Transform transform{};
	Transform offsetTransform{};
	//Camera
	Camera cam{ 0 };
	CameraData camData{};



	void CameraControl();

};

