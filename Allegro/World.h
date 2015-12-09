#pragma once
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
	Vector2D dimensions;
	Vector2D offset;
	int gridSize;
	GridTile Tile[128][64];
	Buffer Background;
	Block Blocks[128][64];
	BlockType Type[15];

	World(){}
	World(Vector2D s, int gs);

	

	GridTile getClickedTile(Vector2D inLoc);

	void Tick();

	bool Load(const char file[64]);
	bool Save(const char file[64]);

private:
};

