#include "Player.h"

Player::Player(){
	run = SpriteSheet(al_load_bitmap("Textures/running_e.png"), 64, 128, 11);
	fall = SpriteSheet(al_load_bitmap("Textures/fall_e.png"), 64, 128, 3);
	still = SpriteSheet(al_load_bitmap("Textures/idle_e.png"), 64, 128, 6);
}

void Player::Run(Vector2D vel){
	Clamp(velocity.x += 0.1f, 0.f, vel.x);
	Clamp(velocity.y += 0.1f, 0.f, vel.y);

	position += velocity;
}

void Player::Tick(float delta){

}