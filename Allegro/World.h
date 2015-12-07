#pragma once
#include "Engine.h"

struct GridTile{
	Vector2D location;
	bool occupied;
	int id;

	GridTile(){ occupied = false; }
};

class World{
public:
	Vector2D dimensions;
	Vector2D offset;
	int gridSize;
	GridTile Tile[128][64];

	World(){}
	World(Vector2D s, int gs);

	

	GridTile getClickedTile(Vector2D inLoc);

	void Tick();

private:
};

