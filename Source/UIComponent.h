#pragma once

#include "Engine.h"

//Abstract class for all UI components
class UIComponent{
public:
	//Width of the component
	int width;

	//Height of the component
	int height;

	//Position on the screen of the component
	Vector2D position;

	//ID of the component
	int id;

	//Cursor that 
	ALLEGRO_SYSTEM_MOUSE_CURSOR cursor;

	UIComponent(){}

	virtual void onHoverIn() = 0;
	virtual void onHoverOut() = 0;
	virtual void onMouseDown() = 0;
	virtual void onMouseUp() = 0;
	virtual void handleKeyInput(ALLEGRO_EVENT *ev) = 0;
	virtual void Draw() = 0;
protected:
	ALLEGRO_BITMAP* tex;
	ALLEGRO_FONT* RobotoSmall;
	ALLEGRO_FONT* RobotoMedium;
	ALLEGRO_FONT* RobotoLarge;
};