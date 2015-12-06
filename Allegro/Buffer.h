#pragma once

#include "Engine.h"

struct Buffer {
public:
	//main components of struct
	ALLEGRO_BITMAP *image;
	float x;
	float y;
	float dx;
	float dy;
	bool bdx;
	bool bdy;

protected:
};
