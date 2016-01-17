#pragma once

#include "Engine.h"

class Button : public UIComponent{
public:
	char text[256];
	ALLEGRO_COLOR bgColor;		//all colours on button
	ALLEGRO_COLOR textColor;
	void (*onDown)();

	Button(){}
	Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], void (*down)());		

	void handleKeyInput(ALLEGRO_EVENT *ev);
	void onHoverIn();		//all events that occur as user interacts with the button
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();
private:
	ALLEGRO_FONT* roboto;		//font used for text

};