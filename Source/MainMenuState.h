#pragma once

#include "Engine.h"
#include "Button.h"
#include "TextBox.h"
#include "Online.h"

//Gamestate containing the main menu of the game
class MainMenuState : public GameState {
public:
	//Time that the splash has been on screen
	float splashTime;

	//Whether or not to draw the splash
	bool bDrawSplash;

	//Actual splash image
	ALLEGRO_BITMAP* splash;
	
	//Whether the window is fullscreen
	bool bFullscreen = false;

	//Array of all UI components on screen
	UIComponent* AllUIComponents[10];

	//Large size of Allegro font
	ALLEGRO_FONT* LargeRoboto;

	//Background images
	Buffer Background[3];
	
	//Image of controls
	ALLEGRO_BITMAP* controls;

	//Whether to display the controls
	static bool bDisplayControls;

	//Initialize the Gamestate
	void Init();

	//Handle all input
	void HandleEvents(ALLEGRO_EVENT *ev);

	//Called every frame
	void Tick(float delta);

	//Draws Gamestate to the screen
	void Draw();

	//Destroy the game state
	void Destroy();

	MainMenuState();
	~MainMenuState();
};
namespace MainMenu{
	void PlayGame();
	void LoadEditor();
	void OpenSettings();
	void ToggleFullscreen();
}

void PushLevel();