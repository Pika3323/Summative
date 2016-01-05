#pragma once

#include "Engine.h"

class TextBox : public UIComponent{
public:
	char placeholder[256];
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR textColor;
	ALLEGRO_COLOR pColor;
	ALLEGRO_USTR* TText;

	int caret;


	TextBox(){}
	TextBox(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char placeholder[]);

	~TextBox();

	void handleKeyInput(ALLEGRO_EVENT *ev);
	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void UpdateText();
	void Draw();
	ALLEGRO_FONT* roboto;
};