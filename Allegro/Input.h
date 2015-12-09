#pragma once

#include "Engine.h"

enum class InputKeys{

};

struct InputEvent{
	int key;
	void (*func)();
};

class Input{
public:

	InputEvent funcs[300];
	int EventIndex;

	Input(){ EventIndex = 0; }

	void onKeyDown(int key);
	void onKeyUp(int key);
	void onMouseDown(int button);
	void onMouseUp(int button);

	void bindInputfunction(int key, void(*f)());

};