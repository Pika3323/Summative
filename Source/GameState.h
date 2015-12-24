#pragma once

#include "Engine.h"

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

	GameState(){}
	//virtual ~GameState() = 0;
};

