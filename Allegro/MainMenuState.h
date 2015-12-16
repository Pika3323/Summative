#pragma once

#include "Engine.h"
#include "Button.h"

class MainMenuState : public GameState {
public:

	class Button BPlayGame;

	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick();
	void Draw();

	void Destroy();

	MainMenuState();
	~MainMenuState();
};