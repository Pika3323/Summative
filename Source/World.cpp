#include "World.h"


//World Constructor
World::World(Vector2D s, int gs){
	dimensions = s;
	gridSize = gs;
	offset = Vector2D(0.f, 0.f);

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 64; j++) {
			Blocks[i][j] = Block();
		}
	}

	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 64; j++){
			Tile[i][j].location = Vector2D(i * gridSize, j * gridSize);
			Blocks[i][j].position = Vector2D(i * gridSize, j * gridSize);
			Tile[i][j].x = i;
			Tile[i][j].y = j;
		}
	}

}

//Returns which tile was clicked based on the location of the click
GridTile* World::GetClickedTile(Vector2D inLoc){
	return &Tile[(int)ceil(inLoc.x) / gridSize][(int)ceil(inLoc.y) / gridSize];
}

void World::PlaceBlock(GridTile* Target, EBlockType Type){
	Blocks[Target->x][Target->y].position = Target->location;
	Blocks[Target->x][Target->y].type = Type;
	Blocks[Target->x][Target->y].bSpawned = true;
	Target->occupied = true;
}

void World::DestroyBlock(GridTile* Target){
	Blocks[Target->x][Target->y].bSpawned = false;
	Target->occupied = false;
}

void World::PlaceEnemy(GridTile* Target, EnemyType Type, std::vector<Enemy*> &All){
	//if (Type == EnemyType::E_Cinas) {
	//	All->pushback(Cinas(Vector2D(Target->location.x, Target->location.y)));
	//}
	if (Type == EnemyType::E_Dankey) {
		All->push_back(new Dankey(Vector2D(Target->location.x, Target->location.y)));
	}
	//if (Type == EnemyType::E_Yash) {
	//	All->pushback(Yash(Vector2D(Target->location.x, Target->location.y)));
	//}
}

//Called on every frame For Logic Updates.
void World::Tick(float delta){
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
				//fseek(fptr, sizeof(Block)*i*j, SEEK_SET);
				fread(&Blocks[i][j], sizeof(Block), 1, fptr);
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
		for (int i = 0; i < 128; i++){
			for (int j = 0; j < 64; j++){
				fwrite(&Blocks[i][j], sizeof(Block), 1, fptr);
			}
		}
		fclose(fptr);

		return true;
	}
	else{
		return false;
	}
}

void World::moveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay, int w, int h){
	//Move level
	grid.offset += delta;
	bg.offset += delta / 2;
	block.offset += delta;
	notplay.offset += delta;
	offset += delta;

	if (offset.x > 0) {
		grid.offset.x = 0;
		bg.offset.x = 0;
		block.offset.x = 0;
		notplay.offset.x = 0;
		offset.x = 0;
	}
	else if (offset.x < dimensions.x  * -1 + w){
		grid.offset.x = dimensions.x  * -1 + w;
		notplay.offset.x = dimensions.x  * -1 + w;
		bg.offset.x = dimensions.x  * -0.5 + w / 2;
		block.offset.x = dimensions.x * -1 + w;
		offset.x = dimensions.x  * -1 + w;
	}

	if (offset.y > 0){
		grid.offset.y = 0;
		notplay.offset.y = 0;
		bg.offset.y = 0;
		block.offset.y = 0;
		offset.y = 0;
	}
	else if (offset.y < dimensions.y * -1 + h){
		grid.offset.y = dimensions.y * -1 + h;
		notplay.offset.y = dimensions.y * -1 + h;
		bg.offset.y = (dimensions.y * -0.5f) + (h / 2);
		block.offset.y = dimensions.y * -1 + h;
		offset.y = dimensions.y * -1 + h;
	}
	
}