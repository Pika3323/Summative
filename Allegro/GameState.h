#pragma once

#include "Engine.h"

class GameState
{
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents();
	void Tick();
	void Draw();

	GameState();
	virtual ~GameState();
};

