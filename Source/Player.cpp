#include "Player.h"

Player::Player(int Height, int Width){
	run = SpriteSheet(al_load_bitmap("Textures/running_e.png"), 64, 128, 11);
	fall = SpriteSheet(al_load_bitmap("Textures/fall_e.png"), 64, 128, 3);
	still = SpriteSheet(al_load_bitmap("Textures/idle_e.png"), 64, 128, 6);
	ActualHeight = Height;
	ActualWidth = Width;
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

}

//Called every frame
void Player::Tick(float delta){
	//All of the animation code
	if (bRunning && bOnGround){
		texture = run.GetFrameBitmap();
		run.PushFrame();
		position += velocity;
	}
	else if (bOnGround){
		texture = still.GetFrameBitmap();
		still.PushFrame();
		position += velocity;
	}
	else if (!bOnGround){
		texture = fall.GetFrameBitmap();
		fall.PushFrame();
		position += velocity;
	}
}