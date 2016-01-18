#pragma once

#include "Engine.h"

//An enum representing the different types of blocks that exist
enum class EBlockType{
	B_Rainbow,			//All possible block types in the game
	B_Brick,
	B_Grass,
	B_Dirt,
	B_Stone,
	B_Fancy,
	B_Mossy,
	B_BackgroundBrick,
	B_FinishFlag
};

//A definition of a single type of block
struct BlockType{
	//The name of the type of block
	char name[32];

	//The texture to use to draw that type of block
	ALLEGRO_BITMAP *texture;

	//Whether this type of block has collision
	bool bCollision;

	//If true, block texture will have random direction
	bool bRandomD;

	BlockType(){}
	BlockType(const char n[16], ALLEGRO_BITMAP* tex, bool collision, bool randomD);
};

//A single block in the world
class Block{
public:
	//The block's location in the level
	Vector2D position;	

	//The block's offset relative to the player (for rendering purposes)
	Vector2D offset;	

	//Whether the block has been placed in the world yet
	bool bSpawned;

	//Whether this block has collision
	bool bCollision;

	//Direction for the block
	int Direction;

	//The block's type
	EBlockType type;

	Block(){ bSpawned = false; Direction = 0; }
	Block(Vector2D pos, EBlockType t, int d);	

	//Draws the block to the screen
	void Draw(ALLEGRO_BITMAP* typeTex);
private:
	
};