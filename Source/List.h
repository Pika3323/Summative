#pragma once

#include "Engine.h"
#include "World.h"
#include "Button.h"
#include "Online.h"

class List : public UIComponent{
public:
	float transitionLength;
	float transtionedTime;

	WorldLevelData Level;

	Button Play;

	void handleKeyInput(ALLEGRO_EVENT *ev);
	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();

	List();
	List(Vector2D position, WorldLevelData Level);
};

void PlayGame();