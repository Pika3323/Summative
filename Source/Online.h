#pragma once

#include "Engine.h"

enum LevelData{
	File,
	Completions,
	Tries,
	Votes
};

struct LevelVotes{
	int up;
	int down;
};

class Online{
public:
	static LevelVotes v;
	static int completions;
	static int attempts;

	//Upload a NEW level to the server and add its information to the database
	static void PostLevel(const char* LevelName);

	//Update an EXISTING level
	static void UpdateLevel(const char* LevelName, int id, LevelData data);

	//Delete a level
	static void DeleteLevel(int id);

	//Get data from a level on the server
	static void GetLevelData(int id);

	static void SaveLevel(int id);
};

