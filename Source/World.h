#pragma once
#include "Block.h"
#include "Buffer.h"
#include "Engine.h"

struct GridTile{
	Vector2D location;
	bool occupied;
	int id;
	int x;
	int y;

	GridTile(){ occupied = false; }
};

class World{
public:
	char name[64];
	Vector2D dimensions;
	Vector2D offset;
	int gridSize;
	GridTile Tile[128][64];
	Buffer Background;
	Block Blocks[128][64];
	BlockType Type[15];
	bool bPlay;

	World(){}
	World(Vector2D s, int gs);

	

	GridTile* GetClickedTile(Vector2D inLoc);

	void PlaceBlock(GridTile* Target, EBlockType Type);
	void DestroyBlock(GridTile* Target);

	void Tick(float delta);

	bool Load(const char file[64]);
	bool Save(const char file[64]);

	void moveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay, int w, int h);
private:
};

