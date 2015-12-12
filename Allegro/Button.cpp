#include "Button.h"

Button::Button(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char t[], ALLEGRO_DISPLAY *d){
	tex = al_create_bitmap(w, h);
	width = w;
	height = h;
	bgColor = bg;
	textColor = tx;
	position = pos;
	id = i;
	strcpy(text, t);
	roboto = al_load_font("Roboto-Medium.ttf", 14, 0);
	al_set_target_bitmap(tex);
	al_draw_filled_rounded_rectangle(0, 0, w, h, 2, 2, bg);
	al_draw_textf(roboto, tx, w / 2, h / 2, ALLEGRO_ALIGN_CENTER, "%s", t);
	al_set_target_bitmap(al_get_backbuffer(d));
}

void Button::onHover(ALLEGRO_DISPLAY* d){
	al_set_target_bitmap(tex);
	al_draw_filled_rounded_rectangle(0, 0, width, height, 2, 2, al_map_rgb(153, 153, 153));
	al_draw_textf(roboto, textColor, width / 2, width / 2, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_system_mouse_cursor(d, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	al_set_target_bitmap(al_get_backbuffer(d));
}
void Button::onMouseUp(ALLEGRO_DISPLAY* d){
	al_set_target_bitmap(tex);
	al_draw_filled_rounded_rectangle(0, 0, width, height, 2, 2, bgColor);
	al_draw_textf(roboto, textColor, width / 2, width / 2, ALLEGRO_ALIGN_CENTER, "%s", text);
	al_set_system_mouse_cursor(d, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
	al_set_target_bitmap(al_get_backbuffer(d));
}

void Button::draw(){
	al_draw_bitmap(tex, position.x, position.y, 0);
}