#include "Dankey.h"

Dankey::Dankey(Vector2D pos){
	position = pos;
	BarrelDelay = 0;
	ActualHeight = 64;
	ActualWidth = 64;
	velocity = Vector2D(0.f, 0.f);
	attack = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey throw_e.png"), 64, 64, 8);
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey idle_e.png"), 64, 64, 5);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
}

void Dankey::Tick(float delta){
	if (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		if (Vector2D(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position - position).Magnitude() <= 320 && dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
			attack.GetFrameBitmap(this->texture);
			attack.PushFrame();
		}
		else {
			still.GetFrameBitmap(this->texture);
			still.PushFrame();
		}
	}

	if (position.x - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x > 0){
		direction = ECharacterDirection::R_Left;
	}
	else{
		direction = ECharacterDirection::R_Right;
	}
}

void Dankey::Run(Vector2D velocity){

}

void Dankey::Jump(){

}

void Dankey::Die(){

}
