#pragma once

#include "World.h"
#include "Buffer.h"
#include "Engine.h"

class PlayState : public GameState {
public:

	class World* CurrentWorld;
	Character TinTin;	//TinTin character
	Gravity CurrentGrav;		//current world gravity
	Buffer notPlayingBuff; //block buffer for when not playing
	Buffer blockBuff;	//play buffer for blocks
	Buffer dubBuff;	//buffer for grid
	Buffer Background;	//buffer for background
	Vector2D Clicked;	//The location of a click
	struct GridTile clickedTile;	//The clicked tile from the world grid
	bool bClicked = false;	//Whether a click was registered
	bool bRedraw = false;	//Whether to redraw the screen
	EBlockType SelectedBlock = EBlockType::B_Brick;		//the block type the user selects
	bool DeleteMode = false;
	bool TinTinGrav = true;
	Vector2D moveDelta = Vector2D(0.f, 0.f);

	bool bBoxSelect = false;
	GridTile FirstTile;

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
	void Tick();
	void Draw();

	PlayState();
};