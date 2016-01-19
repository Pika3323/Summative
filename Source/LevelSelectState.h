#pragma once

#include "Engine.h"
#include "List.h"
#include "World.h"
#include "Online.h"
#include "MainMenuState.h"

//Game state which contains a menu to select a saved level to play
class LevelSelectState : public GameState{
public:
	//Username of the player
	char Username[64];
	
	//Whether the local levels menu is active
	static bool bLocalMenu;

	//Vector containing info about all online levels
	std::vector<WorldLevelData> Levels;

	//UI List component visually representing each level
	std::vector<List*> OnlineTiles;

	//Vector containing info about all local levels
	std::vector<WorldLevelData> LocalLevels;

	//UI List component visually representing each level
	std::vector<List*> LocalTiles;

	//Vector of all UI Components
	std::vector<UIComponent*> Components;

	//Initialize Gamestate
	void Init();

	//Handles all input
	void HandleEvents(ALLEGRO_EVENT *ev);

	//Called on every frame
	void Tick(float delta);

	//Draws Gamestate to the screen
	void Draw();

	//Destroy the Gamestate
	void Destroy();

	LevelSelectState();
	~LevelSelectState();
	
	//Frame's Mouse State with an offset of 1
	ALLEGRO_MOUSE_STATE mstate;

	//Large size Allegro font
	ALLEGRO_FONT* LargeRoboto;
};

void ViewOnline();
void ViewLocal();