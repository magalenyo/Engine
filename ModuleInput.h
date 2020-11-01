#pragma once
#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_scancode.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	int GetKey(int id) const
	{
		return keyboard[id];
	}

private:
	const Uint8 *keyboard = NULL;
};