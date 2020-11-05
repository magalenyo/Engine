#pragma once
#include "Module.h"
class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool CleanUp();
	update_status Update();
	update_status PreUpdate();

};

