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

	void move(const CameraMovement &movementType);
	void rotate(const CameraRotation& rotationType);
	

private:
	Frustum frustum;
	float verticalSpeed = 1.0f;
	float horizontalSpeed = 1.0f;
	float rotationSpeed = 30.0f;


	void resetSpeed();
	void increaseSpeed();
};
