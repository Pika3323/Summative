#pragma once
#include "Block.h"
#include "Buffer.h"
#include "Engine.h"
#include "Enemy.h"
#include "Dankey.h"


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
	Vector2D dimensions;
	Vector2D offset;
	int gridSize;
	GridTile Tile[128][64];
	Buffer Background;
	Block Blocks[128][64];
	BlockType Type[15];
	class Dankey* dCheck;		//dankey pointer checker 
	class Dankey* dTemp;		//temp for pushing back loading vector
	//Cinas *cCheck;		//Cinas pointer checker			for saving files
	//Cinas cTemp;
	//Yash *yCheck;		//Yash pointer checker
	//Yash yTemp;
	bool bPlay;
	bool EnemySelect;
	int DankeyCounter;
	int CinasCounter;
	int YashCounter;

	World(){ bPlay = false; }
	World(Vector2D s, int gs);

	GridTile* GetClickedTile(Vector2D inLoc);

	void PlaceBlock(GridTile* Target, EBlockType Type);

	void DestroyBlock(GridTile* Target);

	void PlaceEnemy(GridTile* Target, EnemyType Type, std::vector<Enemy*> *All);	//add each enemy vector in as it is made

	void Tick(float delta);

	bool Load(const char LevelName[64], std::vector<Enemy*> *enemies);
	bool Save(const char LevelName[64], std::vector<Enemy*> enemies);

	void moveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);
	void SetCameraLocation(Vector2D location, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay);
private:
};

