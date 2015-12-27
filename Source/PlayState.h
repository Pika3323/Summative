#pragma once

#include "Engine.h"
#include "World.h"
#include "Buffer.h"
#include "Player.h"
#include "Effects.h"
#include "Block.h"

class PlayState : public GameState {
public:
	//The active World (or level) that is being played
	World* CurrentWorld;

	//The main player
	Player* TinTin;

	//Effects (including gravity) for the current world
	Effects* CurrentEffects;		
	Buffer notPlayingBuff; //block buffer for when not playing
	Buffer blockBuff;	//play buffer for blocks
	Buffer dubBuff;	//buffer for grid
	Buffer Background;	//buffer for background
	Vector2D ClickLocation;	//The location of a click
	GridTile* clickedTile;	//The clicked tile from the world grid
	bool bClicked = false;	//Whether a click was registered
	EBlockType SelectedBlock = EBlockType::B_Brick;		//the block type the user selects
	bool DeleteMode = false;
	bool TinTinGrav = true;
	Vector2D WorldMoveDelta = Vector2D(0.f, 0.f);

	ALLEGRO_BITMAP* output;

	bool bBoxSelect = false;
	bool bFirstBoxSelected = false;
	GridTile* FirstTile;

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