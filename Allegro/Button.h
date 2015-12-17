#pragma once

#include "Engine.h"

class Button{
public:
	char text[256];
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR textColor;
	int width;
	int height;
	Vector2D position;
	int id;
	void (*onDown)();

	Button(){}
	Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], void (*down)());

	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();
private:
	ALLEGRO_BITMAP* tex;
	ALLEGRO_FONT* roboto;

};