#include "World.h"

World::World(Vector2D s, int gs){
	dimensions = s;
	gridSize = gs;

	int index = 0;

	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 15; j++){
			Tile[i][j].location = Vector2D(i * gridSize, j * gridSize);
			Tile[i][j].id = index;
			index++;
		}
	}
}

GridTile World::getClickedTile(Vector2D inLoc){
	return Tile[(int)floor(inLoc.x) % gridSize][(int)floor(inLoc.y) % gridSize];
}