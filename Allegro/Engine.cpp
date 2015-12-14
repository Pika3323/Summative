#include "Engine.h"

void DrawFPS(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, double delta){
	ALLEGRO_COLOR tColor;
	if (1 / delta >= 30){
		 tColor = al_map_rgb(0, 255, 0);
	}
	else{
		tColor = al_map_rgb(255, 0 , 0);
	}

	al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 17, 0, "%.2f FPS", 1 / delta);
	al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 33, 0, "%.2fMS", delta * 1000);
	al_draw_textf(font, tColor, al_get_display_width(display) - 75, 16, 0, "%.2f FPS", 1 / delta);
	al_draw_textf(font, tColor, al_get_display_width(display) - 75, 32, 0, "%.2fMS", delta * 1000);
}