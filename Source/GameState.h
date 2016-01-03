#pragma once

#include "Engine.h"

/**
Game states are used to represent different "states" of the game. 
This could be a menu state, an editor state, or a play state
Game states are like a program that runs inside the main game program.
*/
class GameState {
public:
	virtual void Init() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(ALLEGRO_EVENT *ev) = 0;
	virtual void Tick(float delta) = 0;
	virtual void Draw() = 0;

	virtual void Destroy() = 0;

	ALLEGRO_BITMAP* output;
	bool Initialized = false;
	bool Paused = false;

	GameState(){}
	//virtual ~GameState() = 0;
};

