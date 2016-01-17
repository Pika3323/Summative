#pragma once

#include "Engine.h"

struct Buffer {
	//This is mainly for drawing purposes
	//main components of struct
	ALLEGRO_BITMAP *image;		//actual bitmap to be drawn
	Vector2D offset;		//its world offset
	Vector2D delta;		//if the bitmap should need to move
	bool bdx;
	bool bdy;

	Buffer(){}
	Buffer(ALLEGRO_BITMAP* i, Vector2D ofs, Vector2D d);
};
