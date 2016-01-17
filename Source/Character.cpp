#include "Character.h"

Character::Character(Vector2D xy, int width, int height){
	position = xy;				//all basic information stored
	ActualWidth = width;
	ActualHeight = height;
	bRunning = false;
	bOnGround = false;
}

Character::~Character(){

}

void Character::SetCharacterWorldPosition(Vector2D NewV){
	position = NewV;					//for setting the character position at any point in the game
}

Vector2D Character::GetCharacterWorldPosition(){
	return position;					//for evluating the character position at any point in the game
}

void Character::SetCharacterDirection(ECharacterDirection NewDirection){
	direction = NewDirection;			//setting the character direction
}

ECharacterDirection Character::GetCharacterDirection(){
	return direction;					//getting its direction
}

void Character::Draw(){
	if ((int)direction == 0) {
		al_draw_bitmap(texture, position.x, position.y, 0);			//if it is facing right, draw to right
	}
	else if ((int)direction == 1) {
		al_draw_bitmap(texture, position.x, position.y, ALLEGRO_FLIP_HORIZONTAL);		//if it is facing left, draw flipped
	}
}

void Character::SetupCharacterCollision(Vector2D p, Vector2D s){
	CollisionBounds.position = p;			//setting the hitbox position relative to the character and its size
	CollisionBounds.size = s;
}