#pragma once

#include "Engine.h"

class GUI{
public:

	Buffer GUIBuffer;

	class Component{
	public:
		bool isC;
		Component(){ isC = false; }
		Vector2D position;
		void onMouseDown();
		void onMouseUp();
		void onHover();
	};

	Component* components[1];
	int numComponents;

	class Button : public Component{
	public:
		int width, height;
		ALLEGRO_BITMAP *texture;

		Button(){}
		Button(Vector2D pos, int w, int h, ALLEGRO_BITMAP *tex);
		void onMouseDown();
	};


	GUI(){ numComponents = 0; }

	void onClick(Vector2D loc, int button);
	void addComponent(Component *component);
};