#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleCamera;
class ModuleTime;
class ModuleEditor;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTime* time = nullptr;
	ModuleEditor* editor = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
