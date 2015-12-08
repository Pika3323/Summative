#pragma once

#include "Engine.h"

enum class EBlockType{
	B_Rainbow,
	B_Brick,
	B_Grass,
	B_Dirt,
	B_Stone,
	B_Fancy,
	B_Mossy
};

struct BlockType{

	char name[16];
	ALLEGRO_BITMAP *texture;
	bool bLoaded;

	BlockType(){}
	BlockType(const char n[16], ALLEGRO_BITMAP* tex);
};

class Block{
public:
	Vector2D position;	//The block's location in the level
	Vector2D offset;	//The block's offset relative to the player (for rendering purposes)
	bool bSpawned;
	EBlockType type;


	Block(){ bSpawned = false; }
	Block(Vector2D pos, EBlockType t);
private:
	
};