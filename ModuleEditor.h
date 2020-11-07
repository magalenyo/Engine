#pragma once
#include "Module.h"
#include <string>

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool CleanUp();
	update_status Update();
	update_status PreUpdate();


	void DrawConsole(bool* p_open, std::string logText);
	bool isReady = false;

};

