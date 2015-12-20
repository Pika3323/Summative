#pragma once

#include "Engine.h"

class UIComponent{
public:
	int width;
	int height;
	Vector2D position;
	int id;

	UIComponent();

	void onHoverIn();
	void onHoverOut();
	void onMouseDown();
	void onMouseUp();
	void Draw();
private:
	ALLEGRO_BITMAP* tex;
};