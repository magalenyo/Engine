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

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status Update();
	bool CleanUp();

	void move(const CameraMovement &movementType);
	

private:
	Frustum frustum;
	float verticalSpeed = 1.0f;
	float horizontalSpeed = 1.0f;

};