#include "World.h"


//World Constructor
World::World(Vector2D s, int gs){
	dimensions = s;
	gridSize = gs;
	offset = Vector2D(0.f, 0.f);
	bPlay = false;

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

//Returns which tile was clicked based on the location of the click. Returns NULL if inLoc was invalid
GridTile* World::GetClickedTile(Vector2D inLoc){
	if (inLoc.x < 0 || inLoc.y < 0){
		return NULL;
	}
	else{
		return &Tile[(int)ceil(inLoc.x) / gridSize][(int)ceil(inLoc.y) / gridSize];
	}
}

void World::PlaceBlock(GridTile* Target, EBlockType T){
	Blocks[Target->x][Target->y].bCollision = Type[static_cast<int>(T)].bCollision;
	Blocks[Target->x][Target->y].position = Target->location;
	Blocks[Target->x][Target->y].type = T;
	Blocks[Target->x][Target->y].bSpawned = true;
	Target->occupied = true;
}

void World::DestroyBlock(GridTile* Target){
	Blocks[Target->x][Target->y].bSpawned = false;
	Target->occupied = false;
}

void World::PlaceEnemy(GridTile* Target, EnemyType Type, std::vector<Enemy*> *All){
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
bool World::Load(const char LevelName[64], std::vector<Enemy*> *enemies){
	FILE *fptr = NULL;
	strcpy(name, LevelName);

	DankeyCounter = 0;
	CinasCounter = 0;
	YashCounter = 0;
	dCheck = NULL;

	char FileName[64];
	strcpy(FileName, LevelName);
	strcat(FileName, ".bvl");

	fptr = fopen(FileName, "rb");
	bool bValidLevel = true;

	if (fptr){
		//Read version info
		int Major, Minor;
		fread(&Major, sizeof(int), 1, fptr);
		fread(&Minor, sizeof(int), 1, fptr);

		if (Major < GEngine->VersionMajor || Minor < GEngine->VersionMinor){
			fprintf(stderr, "Game levels of version %d.%d are incompatible with game version %d.%d\n", Major, Minor, GEngine->VersionMajor, GEngine->VersionMinor);
			bValidLevel = false;
		}

		if (bValidLevel) {
			fread(&name, sizeof(char) * 64, 1, fptr);
			for (int i = 0; i < 128; i++) {
				for (int j = 0; j < 64; j++) {
					fread(&Blocks[i][j], sizeof(Block), 1, fptr);
				}
			}
		}

		fread(&DankeyCounter, sizeof(int), 1, fptr);

		for (int i = 0; i < DankeyCounter; i++) {
			fread(&dTemp, sizeof(Vector2D), 1, fptr);
			enemies->push_back(new Dankey(dTemp));
		}

		fclose(fptr);
		return true && bValidLevel;
	}
	else{
		return false;
	}
}

//Saves a level 
bool World::Save(const char LevelName[64], std::vector<Enemy*> enemies) {
	FILE *fptr = NULL;
	DankeyCounter = 0;
	CinasCounter = 0;
	YashCounter = 0;

	char FileName[64];
	strcpy(FileName, LevelName);
	strcat(FileName, ".bvl");

	fptr = fopen(FileName, "wb+");
	if (fptr){
		//Save version info
		fwrite(&GEngine->VersionMajor, sizeof(int), 1, fptr);
		fwrite(&GEngine->VersionMinor, sizeof(int), 1, fptr);
		//Save level name
		fwrite(&name, sizeof(char) * 64, 1, fptr);
		//Save the array of blocks
		for (int i = 0; i < 128; i++){
			for (int j = 0; j < 64; j++){
				fwrite(&Blocks[i][j], sizeof(Block), 1, fptr);
			}
		}
		//count amount of each type of enemy in enemy vector
		for (int i = 0; i < (int)enemies.size(); i++) {
			dCheck = dynamic_cast<Dankey*>(enemies[i]);
			if (!dCheck) {
			}
			else {
				DankeyCounter += 1;
			}
			//add more as new enemies are made
		}
		fwrite(&DankeyCounter, sizeof(int), 1, fptr);
		dCheck = NULL;
		for (int i = 0; i < (int)enemies.size(); i++) {
			dCheck = dynamic_cast<Dankey*>(enemies[i]);
			if (!dCheck) {
			}
			else {
				fwrite(&enemies[i]->position, sizeof(Vector2D), 1, fptr);
			}
			//add more as new enemies are made
		}

		fclose(fptr);

		return true;
	}
	else{
		return false;
	}
}

void World::moveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay){
	int ScreenWidth = GEngine->GetDisplayWidth();
	int ScreenHeight = GEngine->GetDisplayHeight();

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
	else if (offset.x < dimensions.x  * -1 + ScreenWidth){
		grid.offset.x = dimensions.x  * -1 + ScreenWidth;
		notplay.offset.x = dimensions.x  * -1 + ScreenWidth;
		bg.offset.x = dimensions.x  * -0.5 + ScreenWidth / 2;
		block.offset.x = dimensions.x * -1 + ScreenWidth;
		offset.x = dimensions.x  * -1 + ScreenWidth;
	}

	if (offset.y > 0){
		grid.offset.y = 0;
		notplay.offset.y = 0;
		bg.offset.y = 0;
		block.offset.y = 0;
		offset.y = 0;
	}
	else if (offset.y < dimensions.y * -1 + ScreenHeight){
		grid.offset.y = dimensions.y * -1 + ScreenHeight;
		notplay.offset.y = dimensions.y * -1 + ScreenHeight;
		bg.offset.y = (dimensions.y * -0.5f) + (ScreenHeight / 2);
		block.offset.y = dimensions.y * -1 + ScreenHeight;
		offset.y = dimensions.y * -1 + ScreenHeight;
	}
	
}