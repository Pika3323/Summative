#pragma once

#include "Engine.h"
#include "World.h"

<<<<<<< HEAD
//Contains a set of memory
struct MemoryStruct {
=======
struct MemoryStruct {			
>>>>>>> origin/isaac
	char *memory;
	size_t size;
};

//libcurl writeback functions
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
static size_t write_save(void *ptr, size_t size, size_t nmemb, FILE *stream);

//Types of data regarding a level
enum LevelData{
	File,
	Completions,
	Tries,
	Votes
};

//Votes
struct LevelVotes{
	int up;
	int down;
};

//Contains a set of functions for online interaction
namespace Online{
	static LevelVotes v;
	static int completions;
	static int attempts;
	static bool bVerbose;

	static void UserLogin(const char* username, const char* password);

	//Upload a NEW level to the server and add its information to the database
	static void PostLevel(const char* LevelName);

	//Update an EXISTING level
	static void UpdateLevel(const char* LevelName, int id, LevelData data);

	//Delete a level
	static void DeleteLevel(int id);

	//Gets all levels belonging to a user
	static void GetLevelData(const char* username, std::vector<WorldLevelData> &V);

	//Get data from a level on the server
	static WorldLevelData GetLevelData(int id);

	//Get a level from the server by its ID
	static void GetLevel(int id);
};

