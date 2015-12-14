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
	Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], ALLEGRO_DISPLAY* d);

	void onHoverIn(ALLEGRO_DISPLAY* d);
	void onHoverOut(ALLEGRO_DISPLAY* d);
	void onMouseDown(ALLEGRO_DISPLAY* d);
	void onMouseUp(ALLEGRO_DISPLAY* d);
	void draw();
private:
	ALLEGRO_BITMAP* tex;
	ALLEGRO_FONT* roboto;

};