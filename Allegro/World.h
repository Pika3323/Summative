#pragma once
#include "Engine.h"

struct GridTile{
	Vector2D location;
	bool occupied;
	int id;
};

class World{
public:
	Vector2D dimensions;
	int gridSize;
	GridTile Tile[128][64];

	World(){}
	World(Vector2D s, int gs);
	GridTile getClickedTile(Vector2D inLoc);
private:
};

