#pragma once

#include "Engine.h"

class UIComponent{
public:
	int width;
	int height;
	Vector2D position;
	int id;

	UIComponent(){}

	virtual void onHoverIn() = 0;
	virtual void onHoverOut() = 0;
	virtual void onMouseDown() = 0;
	virtual void onMouseUp() = 0;
	virtual void handleKeyInput(ALLEGRO_EVENT *ev) = 0;
	virtual void Draw() = 0;
protected:
	ALLEGRO_BITMAP* tex;
};