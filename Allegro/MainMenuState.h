#pragma once

#include "Engine.h"
#include "Button.h"

class MainMenuState : public GameState {
public:

	class Button BPlayGame;
	class Button BEditorGame;
	class Button BOptions;
	class Button BExit;

	class Button* AllButtons[10];

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

void PlayGame();
void LoadEditor();
void OpenSettings();
