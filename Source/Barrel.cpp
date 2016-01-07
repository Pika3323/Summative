#include "Barrel.h"

Barrel::Barrel(ECharacterDirection d, Vector2D pos){
	position = pos;
	Roll = SpriteSheet(al_load_bitmap("Textures/Objects/Dankeybarrel_e.png"), 128, 16, 8);
	RollDirection = d;
	if (d == ECharacterDirection::R_Left)
		RollSpeed = Vector2D(-8.f, 0.f);
	else
		RollSpeed = Vector2D(8.f, 0.f);
}

void Barrel::Tick(float delta){
	Roll.PushFrame();
	position += RollSpeed;
}

void Barrel::Run(Vector2D velocity){

}

void Barrel::Jump(){

}

void Barrel::Die(){

}
