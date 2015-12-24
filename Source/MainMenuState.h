#pragma once

#include "Engine.h"
#include "Button.h"
#include "TextBox.h"

class MainMenuState : public GameState {
public:

	class Button BPlayGame;
	class Button BEditorGame;
	class Button BOptions;
	class Button BExit;

	class TextBox t;

	UIComponent* AllUIComponents[10];

	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	void Destroy();

	MainMenuState();
	~MainMenuState();
};
namespace MainMenu{
	void PlayGame();
	void LoadEditor();
	void OpenSettings();
}
