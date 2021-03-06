#include "Button.h"

Button::Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], void (*down)()){
	tex = al_create_bitmap(w, h);			//standard button information set
	width = w;
	height = h;
	bgColor = bg;
	textColor = tx;
	position = pos;
	id = i;
	cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK;
	strcpy(text, t);
	roboto = al_load_font("Roboto-Medium.ttf", 14, 0);
	al_set_target_bitmap(tex);
	al_draw_filled_rectangle(0, 0, w, h, bg);
	al_draw_textf(roboto, tx, w / 2, h / 2, ALLEGRO_ALIGN_CENTER, "%s", t);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
	onDown = down;
}

void Button::onHoverIn(){
	al_set_target_bitmap(tex);				//effects when user hovers over button
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(221, 221, 221));
	al_draw_textf(roboto, textColor, width / 2, height / 2 - 7, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}
void Button::onHoverOut(){					//effects when user leaves button
	al_set_target_bitmap(tex);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_filled_rectangle(0, 0, width, height, bgColor);
	al_draw_textf(roboto, textColor, width / 2, height / 2 - 7, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}
void Button::onMouseDown(){					//effects when user clicks button
	al_set_target_bitmap(tex);
	al_draw_filled_rectangle(0, 0, width, height, bgColor);
	al_draw_textf(roboto, textColor, width / 2, width / 2, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
	onDown();
}

void Button::onMouseUp(){					//effects when user stops clicking
	al_set_target_bitmap(tex);
	al_draw_filled_rectangle(0, 0, width, height, bgColor);
	al_draw_textf(roboto, textColor, width / 2, width / 2, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}

void Button::handleKeyInput(ALLEGRO_EVENT *ev){

}
void Button::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}