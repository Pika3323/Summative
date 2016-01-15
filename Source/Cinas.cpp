#include "Cinas.h"

Cinas::Cinas(Vector2D pos){
	Health = 10.f;
	StartPosition = pos;
	Damage = 0.1f;
	position = pos;
	ActualHeight = 32;
	ActualWidth = 32;
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasidle_e.png"), ActualWidth, ActualHeight, 2);
	fall = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasfall_e.png"), ActualWidth, ActualHeight, 2);
	run = SpriteSheet(al_load_bitmap("Textures/Characters/Cinasroll_e.png"), ActualWidth, ActualHeight, 4);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	bOnGround = false;
	bCharacterLocked = false;
	this->SetupCharacterCollision(Vector2D(6.f, 15.f), Vector2D(20.f, 17.f));
}

void Cinas::Tick(float delta, std::vector<Character*> *C){
	World* W = dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld;

	float DistanceToC = Vector2D(position.x - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x + 32, position.y - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.y).Magnitude();
	GridTile* T;
	T = W->GetClickedTile(position); //autoset to where cinas is checking

	
	if ((position.x - (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x + 16)) > 0 && bCharacterLocked){
		direction = ECharacterDirection::R_Left;
		velocity.x = (rand() % (8 + 1 - 2) + 2) * -1;
		T = W->GetClickedTile(position + Vector2D(-32.f, 0.f));
	}
	else if ((position.x - (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x + 16)) < 0 && bCharacterLocked){
		direction = ECharacterDirection::R_Right;
		velocity.x = (rand() % (8 + 1 - 2) + 2);
		T = W->GetClickedTile(position + Vector2D(32.f, 0.f));
	}

	if (T){
		if (bCharacterLocked && W->Blocks[T->x][T->y].bCollision && W->Blocks[T->x][T->y].bSpawned){
			this->Jump();
		}
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
}

void Cinas::Run(Vector2D velocity){

}

void Cinas::Jump(){
	if (bOnGround) {
		velocity.y = (rand() % (25 + 1 - 15) + 15) * -1;

		bOnGround = false;
	}
}

void Cinas::Die(){
	delete this;
}

void Cinas::Collide(Character* OtherCharacter){
	if (dynamic_cast<Player*>(OtherCharacter)) {
		OtherCharacter->Health -= this->Damage;
	}
}

void Cinas::BlockCollide(bool w, int CollisionDirection){
	if (CollisionDirection == 0 || CollisionDirection == 1){
		this->velocity.x = 0;
	}

	else if (CollisionDirection == 2){
		velocity.y = 0;
	}

	else if (CollisionDirection == 3){
		bOnGround = true;
	}

	else if (CollisionDirection == 4){
		bOnGround = false;
	}
}