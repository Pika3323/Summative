#include "World.h"

//World Constructor
World::World(Vector2D s, int gs){
	dimensions = s;
	gridSize = gs;

	int index = 0;

	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 64; j++){
			Tile[i][j].location = Vector2D(i * gridSize, j * gridSize);
			Tile[i][j].id = index;
			index++;
		}
	}
}

//Returns which tile was clicked based on the location of the click
GridTile World::getClickedTile(Vector2D inLoc){
	return Tile[(int)ceil(inLoc.x) / gridSize][(int)ceil(inLoc.y) / gridSize];
}

void World::Tick(){
	//Put all world tick code here
}