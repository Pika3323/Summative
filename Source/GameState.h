#pragma once

#include "Engine.h"

/*
Game states are used to represent different "states" of the game. 
This could be a menu state, an editor state, or a play state
Game states are like a program that runs inside the main game program.
*/
class GameState {
public:
	//Initialize the gamestate
	virtual void Init() = 0;

	//Handles all inputs for the gamestate
	virtual void HandleEvents(ALLEGRO_EVENT *ev) = 0;

	//Called every frame
	virtual void Tick(float delta) = 0;

	//Draws the current gamestate to the screen
	virtual void Draw() = 0;

	//Destroy the current gamestate
	virtual void Destroy() = 0;

	//Whether the state has been paused
	bool Paused = false;

	GameState(){}
};

