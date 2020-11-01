#pragma once
#include "Module.h"
#include <time.h>


class ModuleTime : public Module
{
public:
	ModuleTime() {}
	~ModuleTime() {}

	update_status Update() {
		lastTime = currentTime;
		currentTime = clock();
		return UPDATE_CONTINUE;
	}

	float DeltaTime() {
		return currentTime - lastTime;
	}

private:
	clock_t lastTime = clock();
	clock_t currentTime = clock();
};

