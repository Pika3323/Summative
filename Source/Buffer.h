#pragma once

#include "Engine.h"

//A buffer containing extra position data
struct Buffer {
	//The bitmap containing buffer info
	ALLEGRO_BITMAP *image;

	//Offset from the top left corner of the screen
	Vector2D offset;
	
	//How to move the buffer
	Vector2D delta;

	Buffer(){}
	Buffer(ALLEGRO_BITMAP* i, Vector2D ofs, Vector2D d);
};
