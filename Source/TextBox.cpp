#include "TextBox.h"

TextBox::TextBox(ALLEGRO_COLOR bg, ALLEGRO_COLOR tx, int w, int h, Vector2D pos, int i, const char p[]){
	tex = al_create_bitmap(w, h);
	width = w;
	height = h;
	bgColor = bg;
	textColor = tx;
	position = pos;
	id = i;
	cursor = ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT;
	pColor = al_map_rgb(147, 147, 147);
	strcpy(placeholder, p);
	roboto = al_load_font("Roboto-Regular.ttf", 16, 0);
	al_set_target_bitmap(tex);
	al_draw_line(0, height - 1, width, height - 1, pColor, 1);
	al_draw_textf(roboto, pColor, 4, height / 2 + 8, ALLEGRO_ALIGN_LEFT, "%s", placeholder);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
	caret = 0;
	TText = al_ustr_new("");
}

void TextBox::onMouseDown(){
	GEngine->LockInputToUIComponent(this);
}

void TextBox::onMouseUp(){

}

void TextBox::onHoverIn(){
	//al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_EDIT);
}

void TextBox::onHoverOut(){
	//al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

void TextBox::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}

void TextBox::handleKeyInput(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev->mouse.button == MOUSE_LB){
		Vector2D RelativeLoc = Vector2D(ev->mouse.x - position.x, ev->mouse.y - position.y);

		//Set the caret location based on the location of a click
		for (int i = 0; i < TText->slen; i++) {
			//Create a temporary USTR to store a substring of the text
			ALLEGRO_USTR* temp = al_ustr_new("");
			al_ustr_assign_substr(temp, TText, 0, i);

			//Calculate the position of the caret based on the temporary USTR
			int CarPos = al_get_ustr_width(roboto, temp) + 4;
			if (RelativeLoc.x + 4 < CarPos){
				caret = i - 1;
				break;
			}
		}

		this->UpdateText();
	}

	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev->keyboard.keycode) {
		case ALLEGRO_KEY_RIGHT:
			if (++caret > TText->slen) {
				caret = TText->slen;
			}
			this->UpdateText();
			break;
		case ALLEGRO_KEY_LEFT:
			if (--caret < 0){
				caret = 0;
			}
			this->UpdateText();
			break;
		default:
			break;
		}
	}
	if (ev->type == ALLEGRO_EVENT_KEY_CHAR) {
		switch (ev->keyboard.unichar) {
		case 8:
			//Backspace
			al_ustr_remove_chr(TText, caret - 1);
			if (--caret < 0){
				caret = 0;
			}
			this->UpdateText();
			break;
		case 13:
			//Enter key
			break;
		case 27:
			//Escape key
			GEngine->ReleaseInput();
			break;
		case 127:
			//Delete
			al_ustr_remove_chr(TText, caret);
			this->UpdateText();
			break;

		default:
			if (ev->keyboard.unichar != 0) {
				al_ustr_insert_chr(TText, caret, ev->keyboard.unichar);
				caret++;
				this->UpdateText();
			}
			break;
		}
	}
}

void TextBox::UpdateText(){
	//Set the draw target to this textbox's texture
	al_set_target_bitmap(tex);

	//Clear the existing bitmap to prevent overlapping
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	
	//Draw the text
	al_draw_ustr(roboto, textColor, 4, height / 2 + 8, ALLEGRO_ALIGN_LEFT, TText);

	//Create a temporary USTR to store a substring of the text
	ALLEGRO_USTR* temp = al_ustr_new("");
	al_ustr_assign_substr(temp, TText, 0, caret);

	//Calculate the position of the caret based on the temporary USTR
	int CarPos = al_get_ustr_width(roboto, temp) + 4;

	//Draw the caret
	al_draw_line(CarPos, height / 2 + 8, CarPos, height / 2 + 26, al_map_rgb(0, 0, 0), 1);

	//Reset draw target to the display backbuffer
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	//Free the temporary USTR
	al_ustr_free(temp);
}

TextBox::~TextBox(){
	//Free the text from memory
	al_ustr_free(TText);
}