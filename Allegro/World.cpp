#include "World.h"

//World Constructor
World::World(Vector2D s, int gs){
	dimensions = s;
	gridSize = gs;
	offset = Vector2D(0.f, 0.f);

	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 64; j++){
			Tile[i][j].location = Vector2D(i * gridSize, j * gridSize);
			Tile[i][j].x = i;
			Tile[i][j].y = j;
		}
	}
	for (auto& sub : Blocks){
		for (auto& elem : sub){
			elem = Block();
		}
	}
}

//Returns which tile was clicked based on the location of the click
GridTile World::getClickedTile(Vector2D inLoc){
	return Tile[(int)ceil(inLoc.x) / gridSize][(int)ceil(inLoc.y) / gridSize];
}

//Called on every frame For Logic Updates.
void World::Tick(){
	//Put all world tick code here
}

//Loads a level from a path
bool World::Load(const char file[64]){
	FILE *fptr = NULL;
	fptr = fopen(file, "rb");

	if (fptr){
		for (int i = 0; i < 128; i++){
			for (int j = 0; j < 64; j++)
			{
				fseek(fptr, sizeof(Block)*i, SEEK_SET);
				fread(&Blocks[j][i], sizeof(Block), 1, fptr);
			}
		}

		fclose(fptr);
		return true;
	}
	else{
		return false;
	}
}

//Saves a level 
bool World::Save(const char file[64]){
	FILE *fptr = NULL;
	fptr = fopen(file, "wb+");
	if (fptr){
		for (auto& b : Blocks){
			for (auto& elem : b){
				fwrite(&elem, sizeof(Block), 1, fptr);
			}
		}
		fclose(fptr);

		return true;
	}
	else{
		return false;
	}
}