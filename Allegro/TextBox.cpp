#include "TextBox.h"

TextBox::TextBox(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char p[]){
	tex = al_create_bitmap(w, h);
	width = w;
	height = h;
	bgColor = bg;
	textColor = tx;
	position = pos;
	id = i;
	pColor = al_map_rgb(147, 147, 147);
	strcpy(placeholder, p);
	roboto = al_load_font("Roboto-Regular.ttf", 16, 0);
	al_set_target_bitmap(tex);
	al_draw_line(0, height - 1, width, height - 1, pColor, 1);
	al_draw_textf(roboto, pColor, 4, height / 2 + 8, ALLEGRO_ALIGN_LEFT, "%s", placeholder);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}

void TextBox::onMouseDown(){
	GEngine->LockInputToUIComponent(this);
}

void TextBox::onMouseUp(){

}

void TextBox::onHoverIn(){
	al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT);
}

void TextBox::onHoverOut(){
	al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

void TextBox::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}

void TextBox::handleKeyInput(ALLEGRO_EVENT *ev){
	char temp[2] = { ev->keyboard.unichar, '\0' };
	strcat(text, temp);
	al_set_target_bitmap(tex);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_line(0, height - 1, width, height - 1, pColor, 1);
	al_draw_textf(roboto, textColor, 4, height / 2 + 8, ALLEGRO_ALIGN_LEFT, "%s", text);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}