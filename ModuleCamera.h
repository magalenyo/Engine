#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry/Frustum.h"

typedef unsigned __int8 Uint8;


class ModuleCamera : public Module
{
public:

	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status Update();
	bool CleanUp();

	

private:
	Frustum frustum;

};