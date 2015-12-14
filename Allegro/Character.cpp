#include "Character.h"

Character::Character(Vector2D xy, int width, int height){
	position = xy;
	delay = 5;
	delta = Vector2D(5.f, 5.f);
	curfram = 0;
	framcount = 0;
	ActualWidth = width;
	ActualHeight = height;
	moving = false;
	flipped = false;
}

void Character::DoEv(char CharacEv){
	animation = CharacEv;
	//add 'if' later when more spritesheets are added to check dx to see which facing direction to load
	if (animation == 'i') {
		spritesheet = al_load_bitmap("Textures/idle_e.png");
	}
	else if (animation == 'f') {
		spritesheet = al_load_bitmap("Textures/fall_e.png");
	}

	else if (animation == 'r') {
		spritesheet = al_load_bitmap("Textures/running_e.png");
	}
}
void Character::EvHandle(){
	//idle handles
	if (animation == 'i') {
		maxfram = 6;
	}
	else if (animation == 'f') {
		maxfram = 3;
	}
	else if (animation == 'r') {
		maxfram = 11;
	}
	if (++framcount >= delay) {
		if (++curfram >= maxfram) {
			curfram = 0;
		}
		framcount = 0;
	}
	//add more handles as they are made
}

void Character::Animate(bool flipped){
	if (animation == 'i' && !flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, 0);
	}
	else if (animation == 'i' && flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, ALLEGRO_FLIP_HORIZONTAL);
	}
	if (animation == 'f' && !flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, 0);
	}
	else if (animation == 'f' && flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, ALLEGRO_FLIP_HORIZONTAL);
	}
	if (animation == 'r' && !flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, 0);
	}
	else if (animation == 'r' && flipped) {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, ALLEGRO_FLIP_HORIZONTAL);
	}
	//add more here
}