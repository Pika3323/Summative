#pragma once

#include "Engine.h"

class GameState {
public:
	virtual void Init();

	virtual void Pause();
	virtual void Resume();

	virtual void HandleEvents(ALLEGRO_EVENT *ev);
	virtual void Tick();
	virtual void Draw();

	virtual void Destroy();

	ALLEGRO_BITMAP* output;
	bool Initialized = false;

	GameState();
	virtual ~GameState();
};

