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
};
//A struct containing info on a tile in the world
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
	Vector2D dimensions;		//World size
	Vector2D offset;			//Tracking the world's movement
	int gridSize;				//the size of each block in the game
	GridTile Tile[128][64];		//storing the tiles in the game
	Buffer Background;			//the cloudy background
	Block Blocks[128][64];		//the blocks stored (this is different from a tile)
	BlockType Type[15];			//all types of entities
	class Dankey* dCheck;		//dankey pointer checker 
	Vector2D dTemp;		//temp for pushing back loading vector
	char DankeyPres;		//if dankeys are present print y
	class Cinas *cCheck;		//Cinas pointer checker			for saving files
	Vector2D cTemp;
	char CinasPres;
	bool bPlay;					//Whether or not the user is playing 
	bool EnemySelect;			
	int DankeyCounter;
	int CinasCounter;
	std::vector<EnemyData> EnemiesStored;		//Keep all enemies ever placed stored here
	EnemyData Temp;
	int id;

	World(){ bPlay = false; }
	World(Vector2D s, int gs);

	//Returns which tile was clicked based on the location of the click. Returns NULL if inLoc was invalid
	GridTile* GetClickedTile(Vector2D inLoc);

	void PlaceBlock(GridTile* Target, EBlockType Type);		//called when block is placed

	void DestroyBlock(GridTile* Target);					//called when a block is destroyed

	void PlaceEnemy(GridTile* Target, EnemyType Type);	//add each enemy vector in as it is made

	void Tick(float delta);

	bool Load(const char LevelName[64], std::vector<Character*> *enemies);
	bool Save(const char LevelName[64], std::vector<Character*> enemies);

	void MoveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);

	void FollowCharacter(Character* C, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);

	void SetCameraLocation(Vector2D location, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);
private:
};

//Structure containing data about a level
struct WorldLevelData{
	int VersionMajor, VersionMinor;
	int id;
	char Name[64];
	char Creator[64];
	char Date[64];
	int Attempts;
	int Completions;
	int Upvotes;
	int Downvotes;
	WorldLevelData(){}
	WorldLevelData(int LevelID, const char* LevelName, const char* LevelCreator, const char* LevelCreation, int LevelAttempts, int LevelCompletions, int LevelUpvotes, int LevelDownvotes): id(LevelID), Attempts(LevelAttempts), Completions(LevelCompletions), Upvotes(LevelUpvotes), Downvotes(LevelDownvotes){
		strcpy(Name, LevelName);
		strcpy(Creator, LevelCreator);
		strcpy(Date, LevelCreation);
	}
};
