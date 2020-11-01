#ifndef __ModuleTime_H__
#define __ModuleTime_H__

#include "Module.h"
#include <ctime>

class ModuleTime : public Module
{
public:
	ModuleTime() {}
	~ModuleTime() {}

	bool Init() {
		lastTime = clock();
		currentTime = lastTime;
		return true;
	}

	update_status Update() {
		lastTime = currentTime;
		currentTime = clock();
		return UPDATE_CONTINUE;
	}

	float DeltaTime() {
		return (currentTime - lastTime) / 1000.0f;
	}

private:
	clock_t lastTime;
	clock_t currentTime;
};

#endif