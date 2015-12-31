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
	bool bPlay;
	bool EnemySelect;

	World(){ bPlay = false; }
	World(Vector2D s, int gs);

	

	GridTile* GetClickedTile(Vector2D inLoc);

	void PlaceBlock(GridTile* Target, EBlockType Type);
	void DestroyBlock(GridTile* Target);

	void PlaceEnemy(GridTile* Target, EnemyType Type, std::vector<Enemy*> *All);	//add each enemy vector in as it is made

	void Tick(float delta);

	bool Load(const char LevelName[64]);
	bool Save(const char LevelName[64]);

	void moveWorld(Vector2D delta, Buffer &grid, Buffer &bg, Buffer &block, Buffer &notplay, int w, int h);
private:
};

