#pragma once

#include "Engine.h"

class Block{
public:
	/*Vector2D position;	//The block's location in the level
	Vector2D offset;	//The block's offset relative to the player (for rendering purposes)*/


	Block(){}
private:
	ALLEGRO_BITMAP *texture;	//The block's texture
};