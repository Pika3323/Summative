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



protected:
};
