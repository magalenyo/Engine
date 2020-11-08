#pragma once
#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_scancode.h"

typedef unsigned __int8 Uint8;

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};



class ModuleInput : public Module
{
public:

	enum MouseWheelState
	{
		SCROLLING_UP,
		SCROLLING_DOWN,
		SCROLLING_IDLE
	};
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check for window events last frame
	bool GetWindowEvent(EventWindow ev) const
	{
		return windowEvents[ev];
	}

	MouseWheelState GetMouseWheelState() const
	{
		return mouseWheelState;
	}

private:
	//const Uint8 *keyboard = NULL;
	bool		windowEvents[WE_COUNT];
	KeyState*   keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];

	MouseWheelState	mouseWheelState = MouseWheelState::SCROLLING_IDLE;
};