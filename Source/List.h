#pragma once

#include "Engine.h"
#include "World.h"
#include "Button.h"
#include "Online.h"

//Part of a list that contains information on a level
class List : public UIComponent{
public:
	//Information about the level to be displayed
	WorldLevelData Level;

	//A button to play the level
	Button Play;

	//Handles all input
	void handleKeyInput(ALLEGRO_EVENT *ev);

	//Called when the mouse enters the component
	void onHoverIn();

	//Called when the mouse leaves the component
	void onHoverOut();

	//Called when the component is clicked
	void onMouseDown();

	//Called when the mouse is released
	void onMouseUp();

	//Draws the UI component to the screen
	void Draw();

	List();
	List(Vector2D position, WorldLevelData Level);
};

void PlayGame();