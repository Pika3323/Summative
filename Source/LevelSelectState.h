#pragma once

#include "Engine.h"
#include "List.h"
#include "World.h"
#include "Online.h"

class LevelSelectState : public GameState{
public:
	char Username[64];
	
	std::vector<WorldLevelData> Levels;
	std::vector<List*> Tiles;

	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	void Destroy();

	LevelSelectState();
	~LevelSelectState();
};