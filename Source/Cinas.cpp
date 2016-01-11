#include "Cinas.h"

Cinas::Cinas(Vector2D pos){
	position = pos;
	ActualHeight = 32;
	ActualWidth = 32;
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasidle_e.png"), ActualWidth, ActualHeight, 2);
	fall = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasfall_e.png"), ActualWidth, ActualHeight, 2);
	run = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasroll_e.png"), ActualWidth, ActualHeight, 4);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	bOnGround = false;
	bCharacterLocked = false;
}

void Cinas::Tick(float delta, std::vector<Character*> *C){
	World* W = dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld;

	float DistanceToC = Vector2D(position - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position).Magnitude();
	GridTile* T;
	T = W->GetClickedTile(position); //autoset to where cinas is
	
	if ((position.x - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x) > 0 && bCharacterLocked){
		direction = ECharacterDirection::R_Left;
		velocity.x = -5.f;
		T = W->GetClickedTile(position + Vector2D(-32.f, 0.f));
	}
	else if ((position.x - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x) < 0 && bCharacterLocked) {
		direction = ECharacterDirection::R_Right;
		velocity.x = 5.f;
		T = W->GetClickedTile(position + Vector2D(32.f, 0.f));
	}

	if (bCharacterLocked && W->Blocks[T->x][T->y].bCollision && W->Blocks[T->x][T->y].bSpawned){
		this->Jump();
	}

	if (DistanceToC > 400 && !bCharacterLocked && W->bPlay) {
		still.GetFrameBitmap(texture);
		still.PushFrame();
	}
	else if (DistanceToC < 400 && W->bPlay) {
		bCharacterLocked = true;
		run.GetFrameBitmap(texture);
		run.PushFrame();
	}
	position += velocity;
}

void Cinas::Run(Vector2D velocity){

}

void Cinas::Jump(){
	if (bOnGround) {
		velocity.y = -20.f;

		bOnGround = false;
	}
}

void Cinas::Die(){
	delete this;
}