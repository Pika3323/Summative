#include "Dankey.h"

Dankey::Dankey(Vector2D pos){
	Damage = 15.f;
	Deleted = false;
	position = pos;
	BarrelDelay = 0;
	ActualHeight = 64;
	ActualWidth = 64;
	velocity = Vector2D(0.f, 0.f);
	attack = SpriteSheet(al_load_bitmap("Textures/Characters/Dankeythrow_e.png"), 64, 64, 8);
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Dankeyidle_e.png"), 64, 64, 5);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
}

void Dankey::Tick(float delta, std::vector<Character*> *Curr){
	if (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		if (Vector2D(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position - position).Magnitude() <= 500 && dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
			attack.GetFrameBitmap(this->texture);
			attack.PushFrame();
			BarrelDelay++;
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

	if (this->BarrelDelay == 40) {
		if (this->direction == ECharacterDirection::R_Left){
			Curr->push_back(new Barrel(ECharacterDirection::R_Left, Vector2D(this->position.x, this->position.y + 48)));
			this->BarrelDelay = 0;
		}
		else {
			Curr->push_back(new Barrel(ECharacterDirection::R_Right, Vector2D(this->position.x + 64, this->position.y + 48)));
			this->BarrelDelay = 0;
		}
	}
}

void Dankey::Run(Vector2D velocity){

}

void Dankey::Jump(){

}

void Dankey::Die(){
	delete this;
}
