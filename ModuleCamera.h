#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry/Frustum.h"

typedef unsigned __int8 Uint8;


class ModuleCamera : public Module
{
public:

	enum CameraMovement {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD
	};

	enum CameraRotation {
		ROLL_POSITIVE,
		ROLL_NEGATIVE,
		PITCH_POSITIVE,
		PITCH_NEGATIVE,
		YAW_POSITIVE,
		YAW_NEGATIVE
	};

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status Update();
	bool CleanUp();

	void Move(const CameraMovement &movementType);
	void Rotate(const CameraRotation& rotationType);
	void OnWindowResized(int width, int height);
	void SetHorizontalFov(int fov);
	void SetVerticalFov(int fov);
	void SetNearPlaneDistance(float dist);
	void SetFarPlaneDistance(float dist);
	

private:
	Frustum frustum;
	float verticalSpeed = 1.0f;
	float horizontalSpeed = 1.0f;
	float rotationSpeed = 30.0f;


	void ResetSpeed();
	void IncreaseSpeed();
	
};
