#pragma once

#include "Engine.h"

class List : public UIComponent{
public:
	float transitionLength;
	float transtionedTime;

	void handleKeyInput(ALLEGRO_EVENT *ev);
	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();
};