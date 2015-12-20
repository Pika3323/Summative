#include "UIComponent.h"

UIComponent::UIComponent(){
	tex = al_create_bitmap(width, height);
}

void UIComponent::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}