#pragma once

#include "Engine.h"

struct Buffer {
public:
	//main components of struct
	ALLEGRO_BITMAP *image;
	Vector2D offset;
	Vector2D delta;
	bool bdx;
	bool bdy;

	Buffer(){}
	Buffer(ALLEGRO_BITMAP* i, Vector2D ofs, Vector2D d);

protected:
};
