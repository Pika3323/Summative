#include "Character.h"

Character::Character(Vector2D xy, int width, int height){
	position = xy;
	delay = 5;
	delta = Vector2D(5.f, 5.f);
	curfram = 0;
	framcount = 0;
	ActualWidth = width;
	ActualHeight = height;
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
	//else if ()
}
void Character::EvHandle(){
	//idle handles
	if (animation == 'i') {
		maxfram = 6;
		if (++framcount >= delay) {
			if (++curfram >= maxfram) {
				curfram = 0;
			}
			framcount = 0;
		}
	}
	if (animation == 'f') {
		maxfram = 3;
		if (++framcount >= delay) {
			if (++curfram >= maxfram) {
				curfram = 0;
			}
			framcount = 0;
		}
	}
	//add more handles as they are made
}

void Character::Animate(){
	if (animation == 'i') {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, 0);
	}
	if (animation == 'f') {
		al_draw_bitmap_region(spritesheet, (curfram * ActualWidth), 0, ActualWidth, ActualHeight, position.x, position.y, 0);
	}
	//add more here
}