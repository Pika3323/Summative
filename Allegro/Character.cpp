#include "Character.h"

Character::Character(Vector2D xy, int width, int height){
	position = xy;
	delay = 5;
	curfram = 0;
	framcount = 0;
	ActualWidth = width;
	ActualHeight = height;
	bMoving = false;
	bFlipped = false;
	direction = ECharacterDirection::R_Right;
	running = al_load_bitmap("Textures/running_e.png");
	falling = al_load_bitmap("Textures/fall_e.png");
	idle = al_load_bitmap("Textures/idle_e.png");
	spritesheet = falling;
}

void Character::DoEv(char CharacEv){
	if (animation != CharacEv) {
		curfram = 0;
		framcount = 0;
	}
	animation = CharacEv;
	if (animation == 'i') {
		spritesheet = idle;
	}
	else if (animation == 'f') {
		spritesheet = falling;
	}
	else if (animation == 'r') {
		spritesheet = running;
	}
}
void Character::EvHandle(){
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

Character::~Character(){
	al_destroy_bitmap(running);
	al_destroy_bitmap(idle);
	al_destroy_bitmap(falling);
}

void Character::SetCharacterDirection(ECharacterDirection NewDirection){
	direction = NewDirection;
}

void Character::Draw(){
	al_draw_bitmap(texture, position.x, position.y, static_cast<int>(direction));
}