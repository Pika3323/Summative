#pragma once

#include "Engine.h"

class MainMenuState : public GameState {
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents();
	void Tick();
	void Draw();
};