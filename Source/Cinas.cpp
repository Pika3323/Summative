#include "Cinas.h"

Cinas::Cinas(Vector2D pos){
	Health = 10.f;
	Damage = 0.2f;
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

	float DistanceToC = Vector2D(position.x - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->Oiram->position.x + 32, position.y - dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->Oiram->position.y).Magnitude();
	GridTile* T = W->GetClickedTile(position); //autoset to where cinas is checking
	GridTile* F = W->GetClickedTile(position);

	
	if ((position.x - (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->Oiram->position.x + 16)) > 0 && bCharacterLocked){
		direction = ECharacterDirection::R_Left;			//if the character is to the left of the cinas, move left
		velocity.x = (rand() % (8 + 1 - 2) + 2) * -1;
		T = W->GetClickedTile(position + Vector2D(-32.f, 0.f));
		F = W->GetClickedTile(position + Vector2D(-32.f, -32.f));
	}
	else if ((position.x - (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->Oiram->position.x + 16)) < 0 && bCharacterLocked){
		direction = ECharacterDirection::R_Right;		//if the character is to the right of the cinas, move right
		velocity.x = (rand() % (8 + 1 - 2) + 2);
		T = W->GetClickedTile(position + Vector2D(32.f, 0.f));
		F = W->GetClickedTile(position + Vector2D(32.f, -32.f));
	}

	if (T && F){
		if (bCharacterLocked && W->Blocks[T->x][T->y].bCollision && W->Blocks[T->x][T->y].bSpawned){
			this->Jump();
		}
		/*if (bCharacterLocked && (W->Blocks[F->x][F->y].bCollision || W->Blocks[F->x][F->y].bSpawned)){
			this->Jump();
		}*/
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
	else if (DistanceToC > 700 && W->bPlay){
		bCharacterLocked = false;
	}
}

void Cinas::Run(Vector2D velocity){

}

void Cinas::Jump(){
	if (bOnGround) {
		velocity.y = (rand() % (25 + 1 - 15) + 15) * -1;			//adding some variability to the jump height

		bOnGround = false;
	}
}

void Cinas::Die(){
	delete this;
}

void Cinas::Collide(Character* OtherCharacter){
	if (dynamic_cast<Player*>(OtherCharacter)) {		//if it is a player, do damage
		OtherCharacter->Health -= this->Damage;
	}
}

void Cinas::BlockCollide(bool w, ECollisionDirection direction){
	if (direction == ECollisionDirection::Right || direction == ECollisionDirection::Left){
		this->velocity.x = 0;
	}

	else if (direction == ECollisionDirection::Top){
		velocity.y = 0;
		position.y += 32.f;
	}

	else if (direction == ECollisionDirection::DownStay){
		bOnGround = true;
		velocity.y = 0;
	}

	else if (direction == ECollisionDirection::DownStop){
		bOnGround = false;
	}
}