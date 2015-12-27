#include "Character.h"

Character::Character(Vector2D xy, int width, int height){
	position = xy;
	ActualWidth = width;
	ActualHeight = height;
	bRunning = false;
	bOnGround = false;
	bFlipped = false;

	//Set the character's default direction to the right
	direction = ECharacterDirection::R_Right;
}

Character::~Character(){

}

void Character::SetCharacterWorldPosition(Vector2D NewV){
	position = NewV;
}

Vector2D Character::GetCharacterWorldPosition(){
	return position;
}

void Character::SetCharacterDirection(ECharacterDirection NewDirection){
	direction = NewDirection;
}

ECharacterDirection Character::GetCharacterDirection(){
	return direction;
}

void Character::Draw(){
	if ((int)direction == 0) {
		al_draw_bitmap(texture, position.x, position.y, 0);
	}
	else if ((int)direction == 1) {
		al_draw_bitmap(texture, position.x, position.y, ALLEGRO_FLIP_HORIZONTAL);
	}
}