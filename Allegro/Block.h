#pragma once

#include "Engine.h"

enum class BlockType{
	B_Brick,
	B_Fancy,
	B_Rainbow
};

class Block{
public:
	Vector2D position;	//The block's location in the level
	Vector2D offset;	//The block's offset relative to the player (for rendering purposes)
	bool bSpawned;
	ALLEGRO_BITMAP *texture;	//The block's texture
	BlockType type;


	Block(){ bSpawned = false; }
	Block(Vector2D pos, ALLEGRO_BITMAP *tex);
private:
	
};