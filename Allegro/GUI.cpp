#include "GUI.h"

GUI::Button::Button(Vector2D pos, int w, int h, ALLEGRO_BITMAP *tex){
	position = pos;
	width = w;
	height = h;
	texture = tex;
	isC = true;
}
void GUI::Button::onMouseDown(){
	printf("You clicked the button!\n");
}

void GUI::onClick(Vector2D pos, int button){
	for (auto& comp : components){
		if (comp->isC){
			if (pos.x >= comp->position.x && pos.y >= comp->position.y && pos.x <= comp->position.x + static_cast<GUI::Button*>(comp)->width && pos.y <= comp->position.y + static_cast<GUI::Button*>(comp)->height){
				static_cast<GUI::Button*>(comp)->onMouseDown();
			}
		}
	}
}