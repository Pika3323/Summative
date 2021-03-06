#pragma once

#include "Engine.h"
#include "List.h"
#include "World.h"
#include "Online.h"

class LevelSaveState : public GameState{
public:
	char Username[64];
	static bool bLocalMenu;

	std::vector<WorldLevelData> Levels;
	std::vector<List*> OnlineTiles;
	std::vector<WorldLevelData> LocalLevels;
	std::vector<List*> LocalTiles;

	std::vector<UIComponent*> Components;

	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	void Destroy();

	LevelSaveState();
	~LevelSaveState();
	ALLEGRO_MOUSE_STATE mstate;
	ALLEGRO_FONT* LargeRoboto;
};
