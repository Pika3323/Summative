#pragma once

#include "Engine.h"

//A button that can be pressed
class Button : public UIComponent{
public:
	//The button's text
	char text[256];

	//The background colour of the button
	ALLEGRO_COLOR bgColor;

	//Color of the button's text
	ALLEGRO_COLOR textColor;

	//Function to run when the button is pressed
	void (*onDown)();

	Button(){}
	Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], void (*down)());		

	//Handle any key events for the button
	void handleKeyInput(ALLEGRO_EVENT *ev);

	//Called when the mouse enters the button
	void onHoverIn();

	//Called when the mouse is not over the button
	void onHoverOut();

	//Called when the button is pressed
	void onMouseDown();

	//Called when the button is not being pressed
	void onMouseUp();

	//Draws the button
	void Draw();
private:
	//The button's font
	ALLEGRO_FONT* roboto;
};