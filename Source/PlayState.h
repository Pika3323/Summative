#pragma once

#include "Engine.h"
#include "World.h"
#include "Buffer.h"
#include "Player.h"
#include "Physics.h"
#include "Block.h"
#include "Button.h"
#include "Enemy.h"
#include "Dankey.h"

class PlayState : public GameState {
public:
	//The active World (or level) that is being played
	class World* CurrentWorld;

	//The main player
	Player* Oiram;

	//Vector coordinate for the player from an earlier frame to calculate a delta
	Vector2D PlayerOldPosition;
	Vector2D Debug;

	//Effects (including gravity) for the current world
	class Physics* Fyzix;	

	//block buffer for when not playing
	Buffer notPlayingBuff; 

	//play buffer for blocks
	Buffer BlockBuffer;	

	//buffer for grid
	Buffer GridBuffer;	

	//buffer for background
	Buffer Background;	

	//A buffer for the UI
	Buffer UI;

	std::vector<Buffer> SelectBlock;

	int UIOffset;

	ALLEGRO_SAMPLE* music;

	//The location of a click
	Vector2D ClickLocation;	

	//character type checker
	Character* TypeChecker;

	//The clicked tile from the world grid
	struct GridTile* clickedTile;	

	//Whether a click was registered
	bool bClicked = false;	

	//the block type the user selects
	EBlockType SelectedBlock = EBlockType::B_Brick;	

	//Character start position
	Vector2D CharacterStart;

	//bool for if user is changing start position
	bool bChangingStart;

	//for fixing character movement
	ECharacterDirection Priority;

	// for checking what happening in collision physics
	int ColChecker;

	//Characters in the world
	std::vector<Character*> CurrCharacters;

	//make a vector for each enemy type as they are made
	
	EnemyType SelectedEnemy;
	
	bool TinTinGrav = true;
	
	Vector2D WorldMoveDelta = Vector2D(0.f, 0.f);

	ALLEGRO_BITMAP* output;
	
	ALLEGRO_BITMAP* BoxSelectCursor;

	ALLEGRO_BITMAP* HealthBar;

	ALLEGRO_BITMAP* DankeyTemp;
	
	ALLEGRO_BITMAP* CinasTemp;
	
	ALLEGRO_COLOR HealthBarColour;
	
	ALLEGRO_MOUSE_CURSOR* CircleSelect;


	bool bBoxSelect = false;
	
	bool bFirstBoxSelected = false;

	struct GridTile* FirstTile;

	//A Button to pause the game
	Button* PauseButton;

	//keyboard bool catches
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	//Mouse Drag
	bool bMouseDrag = false;
	Vector2D DragStart;
	float DragTime = 0.f;
	double delta;
	Vector2D DragVelocity = Vector2D(-1.f, -1.f);

	void DestroyCharacter(Character* C);

	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	void Destroy();

	PlayState();
	~PlayState();
};
