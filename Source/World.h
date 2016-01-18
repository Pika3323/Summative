#pragma once
#include "Block.h"
#include "Buffer.h"
#include "Engine.h"
#include "Enemy.h"
#include "Dankey.h"
#include "Cinas.h"

struct EnemyData{
	Vector2D position;
	EnemyType Type;
	EnemyData(){}
	EnemyData(Vector2D pos, EnemyType t) : position(pos), Type(t){}
};
//A struct containing info on a tile in the world
struct GridTile{
	Vector2D location;
	bool occupied;
	int id;
	int x;
	int y;
	EnemyData* E;

	GridTile(){ occupied = false; }
};

class World{
public:
	//The name of the world
	char name[64];

	//The dimensions of the world
	Vector2D dimensions;

	//Offset of the world relative to the top left corner of the screen
	Vector2D offset;

	//Size of the grid
	int gridSize;

	//Array containing the tiles that make up the world
	GridTile Tile[128][64];

	//Buffer for the background
	Buffer Background;

	//Array of all blocks that can be in the world
	Block Blocks[128][64];

	//Array of all types of blocks
	BlockType Type[15];

	class Dankey* dCheck;		//dankey pointer checker 
	Vector2D dTemp;		//temp for pushing back loading vector
	char DankeyPres;		//if dankeys are present print y
	class Cinas *cCheck;		//Cinas pointer checker	for saving files
	Vector2D cTemp;
	char CinasPres;

	//Whether the world is being played
	bool bPlay;

	//Whether an enemy has been selected for placement
	bool EnemySelect;
	
	//Nnumber of dankeys in the save
	int DankeyCounter;

	//Number of Cinass in the save
	int CinasCounter;

	//Vector of stored enemies
	std::vector<EnemyData*> EnemiesStored;

	EnemyData* Temp;

	//ID for the world
	int id;

	World(){ bPlay = false; }
	World(Vector2D s, int gs);

	//Returns which tile was clicked based on the location of the click. Returns NULL if inLoc was invalid
	GridTile* GetClickedTile(Vector2D inLoc);

	//Place a block at the target tile
	void PlaceBlock(GridTile* Target, EBlockType Type);

	//Destroy the block at the target tile
	void DestroyBlock(GridTile* Target);

	//Place an enemy at the target tile
	void PlaceEnemy(GridTile* Target, EnemyType Type);

	//Delete an enemy at the target tile, if one exists
	void DeleteEnemy(GridTile* Target);

	//Called every frame
	void Tick(float delta);

	//Load a level
	bool Load(const char LevelName[64]);

	//Save a level
	bool Save(const char LevelName[64]);

	//Move the world
	void MoveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);

	//Follow a character around in the world
	void FollowCharacter(Character* C, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);

	//Set the location of the camera
	void SetCameraLocation(Vector2D location, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);
};

//Structure containing data about a level
struct WorldLevelData{
	//Version that the level was saved with
	int VersionMajor, VersionMinor;

	//ID of the level
	int id;

	//Name of the level
	char Name[64];
	
	//The level's creator
	char Creator[64];

	//The date the level was created
	char Date[64];
	
	//The number of tries on the level
	int Attempts;
	
	//Number of times the level was completed
	int Completions;

	//Number of upvotes the level has
	int Upvotes;

	//Number of downvotes the level has
	int Downvotes;

	WorldLevelData(){}
	WorldLevelData(int LevelID, const char* LevelName, const char* LevelCreator, const char* LevelCreation, int LevelAttempts, int LevelCompletions, int LevelUpvotes, int LevelDownvotes): id(LevelID), Attempts(LevelAttempts), Completions(LevelCompletions), Upvotes(LevelUpvotes), Downvotes(LevelDownvotes){
		strcpy(Name, LevelName);
		strcpy(Creator, LevelCreator);
		strcpy(Date, LevelCreation);
	}
};
