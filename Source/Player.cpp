#include "Player.h"

Player::Player(int Height, int Width){
	run = SpriteSheet(al_load_bitmap("Textures/Characters/running_e.png"), 64, 128, 11);
	fall = SpriteSheet(al_load_bitmap("Textures/Characters/fall_e.png"), 64, 128, 3);
	still = SpriteSheet(al_load_bitmap("Textures/Characters/idle_e.png"), 64, 128, 6);
	ActualHeight = Height;
	ActualWidth = Width;
	texture = al_create_bitmap(Width, Height);
}

void Player::Run(Vector2D vel){
	velocity.x += vel.x;

	if (velocity.x > 20){
		velocity.x = 10;
	}

	else if (velocity.x < -20){
		velocity.x = -10;
	}

	bRunning = true;

	//this->SetCharacterDirection(static_cast<ECharacterDirection>(velocity.x > 0.f));
}

//Called when the player jumps
void Player::Jump(){
	if (bOnGround) {
		velocity.y = -20.f;

		bOnGround = false;
	}
}

//Called when the player dies
void Player::Die(){
	this->SetCharacterWorldPosition(Vector2D(0, 0));
}

//Called every frame
void Player::Tick(float delta){
	//All of the animation code
	if (bRunning && bOnGround){
		run.GetFrameBitmap(this->texture);
		run.PushFrame();
		position += velocity;
	}
	else if (bOnGround){
		still.GetFrameBitmap(this->texture);
		still.PushFrame();
		position += velocity;
	}
	else if (!bOnGround){
		fall.GetFrameBitmap(this->texture);
		fall.PushFrame();
		position += velocity;
	}
}