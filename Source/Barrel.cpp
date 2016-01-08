#include "Barrel.h"

Barrel::Barrel(ECharacterDirection d, Vector2D pos){
	ActualWidth = 16;
	ActualHeight = 16;
	position = pos;
	Roll = SpriteSheet(al_load_bitmap("Textures/Objects/Dankeybarrel_e.png"), 16, 16, 8);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	RollDirection = d;
	if (d == ECharacterDirection::R_Left)
		velocity = Vector2D(-5.f, 0.f);
	else
		velocity = Vector2D(5.f, 0.f);
}

void Barrel::Tick(float delta){
	if (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		Roll.GetFrameBitmap(this->texture);
		Roll.PushFrame();
		position += velocity;
	}
}

void Barrel::Run(Vector2D velocity){

}

void Barrel::Jump(){

}

void Barrel::Die(){
	delete this;
}
