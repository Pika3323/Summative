#pragma once

#include "Engine.h"

//A textbox for text input
class TextBox : public UIComponent{
public:
	//Placeholder text for an empty textbox
	char placeholder[256];

	//Background color of the textbox
	ALLEGRO_COLOR bgColor;

	//Color of the text
	ALLEGRO_COLOR textColor;

	//Color of the placeholder
	ALLEGRO_COLOR pColor;
	
	//Text entered by the user
	ALLEGRO_USTR* TText;

	//Location of the caret in terms of characters
	int caret;

	TextBox(){}
	TextBox(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char placeholder[]);

	~TextBox();

	//Updates the rendered text
	void UpdateText();

	//Handles all input received to this component
	void handleKeyInput(ALLEGRO_EVENT *ev);

	//Called when the mouse enters the button
	void onHoverIn();

	//Called when the mouse is not over the button
	void onHoverOut();

	//Called when the button is pressed
	void onMouseDown();

	//Called when the button is not being pressed
	void onMouseUp();

	//Draws the textbox
	void Draw();

	//The textbox's font
	ALLEGRO_FONT* roboto;
};