#pragma once

#include "Engine.h"

class TextBox : public UIComponent{
public:
	char text[256];
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR textColor;
	int width;
	int height;
	Vector2D position;
	int id;

	TextBox(){}

	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();
private:
	ALLEGRO_BITMAP* tex;
	ALLEGRO_FONT* roboto;
};