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

	static void PostLevel(const char* LevelName);

	static void UpdateLevel(const char* LevelName, int id, LevelData data);

	static void DeleteLevel(int id);

	static void GetLevelData(int id);

	static void SaveLevel(int id);
};

