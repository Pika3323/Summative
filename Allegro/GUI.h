#pragma once

#include "Engine.h"

class GUI{
public:

	Buffer GUIBuffer;

	class Component{
	public:
		Vector2D position;
	};

	Component* components[16];
	int numComponents;

	class Button : public Component{
	public:
		int width, height;
		ALLEGRO_BITMAP *texture;

		Button(){}
		Button(Vector2D pos, int w, int h, ALLEGRO_BITMAP *tex);

		void onMouseDown();
		void onMouseUp();
		void onHover();
	};


	GUI(){ numComponents = 0; }

	void addComponent(Component *component);
};