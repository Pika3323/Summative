#include "GUI.h"

GUI::Button::Button(Vector2D pos, int w, int h, ALLEGRO_BITMAP *tex){
	position = pos;
	width = w;
	height = h;
	texture = tex;
}