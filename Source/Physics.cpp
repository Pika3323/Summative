#include "Physics.h"

Physics::Physics(Vector2D f){
	Gravforce = f;
}

void Physics::GravTick(std::vector<Character*> All){
	for (int i = 0; i < (int)All.size(); i++) {		//adding gravity to all characters registered
		if (!All[i]->bOnGround && !dynamic_cast<Bullet*>(All[i])){
			All[i]->velocity.y += Gravforce.y;	//could theoretically implement an x gravity if ever wanted to
		}
		if (All[i]->velocity.y >= 50) {
			All[i]->velocity.y = 50;
		}
	}
}

int Physics::ColTick(World* Curr, std::vector<Character*> &All){
	for (int j = 0; j < (int)All.size(); j++) {
		BulletCheck = dynamic_cast<Bullet*>(All[j]);
		PlayerCheck = dynamic_cast<Player*>(All[j]);
		DankeyCheck = dynamic_cast<Dankey*>(All[j]);
		BarrelCheck = dynamic_cast<Barrel*>(All[j]);
		BulletExCheck = dynamic_cast<BulletEx*>(All[j]);
		CinasCheck = dynamic_cast<Cinas*>(All[j]);

		//Stop character from falling through a block
		if (!All[j]->bOnGround && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / Curr->gridSize)][(int)((All[j]->GetCharacterWorldPosition().y + All[j]->ActualHeight) / Curr->gridSize)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / Curr->gridSize)][(int)((All[j]->GetCharacterWorldPosition().y + All[j]->ActualHeight) / Curr->gridSize)].bCollision) {
			if (!BarrelCheck)
				All[j]->SetCharacterWorldPosition(Vector2D(All[j]->GetCharacterWorldPosition().x, Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / Curr->gridSize)][(int)(All[j]->GetCharacterWorldPosition().y) / Curr->gridSize].position.y));
			else
				All[j]->SetCharacterWorldPosition(Vector2D(All[j]->GetCharacterWorldPosition().x, Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / Curr->gridSize)][(int)(All[j]->GetCharacterWorldPosition().y) / Curr->gridSize].position.y + 16));
			ColPos = Vector2D(0.f, 0.f);
			All[j]->bOnGround = true;
			if (All[j]->velocity.y > 0) {
				All[j]->velocity.y = 0;
			}
		}

		//makes characters fall if there is no collidable block under them (and they are not a bullet)
		if (!BulletCheck && !Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / Curr->gridSize)][(int)((All[j]->GetCharacterWorldPosition().y + All[j]->ActualHeight) / Curr->gridSize)].bSpawned){
			All[j]->bOnGround = false;
		}
		else if (!BulletCheck && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / Curr->gridSize)][(int)((All[j]->GetCharacterWorldPosition().y + All[j]->ActualHeight) / Curr->gridSize)].bSpawned && !Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / Curr->gridSize)][(int)((All[j]->GetCharacterWorldPosition().y + All[j]->ActualHeight) / Curr->gridSize)].bCollision) {
			All[j]->bOnGround = false;
		}

		//DO HEAD COLLISION FOR EACH CHARACTER

		//each character in vector has their own collision sets
		if (PlayerCheck) {
			if (Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / 32)][int((All[j]->GetCharacterWorldPosition().y + 50) / 32)].bSpawned && All[j]->velocity.y < 0 && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + (All[j]->ActualWidth / 2)) / 32)][int((All[j]->GetCharacterWorldPosition().y + 50) / 32)].bCollision) {
				ColPos = Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 15)][int((All[j]->GetCharacterWorldPosition().y + 32) / 32)].position;
				All[j]->SetCharacterWorldPosition(Vector2D(All[j]->GetCharacterWorldPosition().x, ColPos.y));
				All[j]->velocity.y = 0;

			}
			for (int i = 33; i < 98; i += 32) {
				if (!static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x - 10) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x - 10) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].type == EBlockType::B_FinishFlag) {
					return 1;
				}
				if (static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 74) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 74) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].type == EBlockType::B_FinishFlag) {
					return 1;
				}
				if (!static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 65) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 65) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {		
					All[j]->velocity.x = -5.f;
				}
				else if (static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 1) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 1) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {
					All[j]->velocity.x = 5.f;
				}
			}
		}
		//add all collisions for each character here
		if (BulletCheck){
			if (!static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + All[j]->ActualWidth) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + All[j]->ActualWidth) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bCollision) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrCharacters.push_back(new BulletEx(All[j]->position, All[j]->direction));
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
			else if (static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bCollision) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrCharacters.push_back(new BulletEx(All[j]->position, All[j]->direction));
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
		}
		if (BulletExCheck){
			if (dynamic_cast<BulletEx*>(All[j])->explode.CurrentFrame == 2){
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
		}
		if (BarrelCheck){
			if (!static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x <= (All[0]->position.x + (All[0]->ActualWidth / 2)) && (All[j]->position.y > (All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
				All[0]->Health -= All[j]->Damage;
			}
			else if (static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x >= All[0]->position.x && (All[j]->position.y >(All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
				All[0]->Health -= All[j]->Damage;
			}
			if (!static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + All[j]->ActualWidth) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + All[j]->ActualWidth) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bCollision) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
			else if (static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y + 8) / 32)].bCollision) {
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
		}
		if (CinasCheck){
			if (!static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x <= (All[0]->position.x + (All[0]->ActualWidth / 2)) && (All[j]->position.y > (All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				All[0]->Health -= All[j]->Damage;
			}
			else if (static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x >= All[0]->position.x && (All[j]->position.y >(All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				All[0]->Health -= All[j]->Damage;
			}
			
		}
		if (DankeyCheck){
			if (!static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x <= (All[0]->position.x + (All[0]->ActualWidth / 2)) && (All[j]->position.y >(All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				All[0]->Health -= All[j]->Damage;
			}
			else if (static_cast<bool>(All[0]->GetCharacterDirection()) && All[j]->position.x >= All[0]->position.x && (All[j]->position.y >(All[0]->position.y + 65) && All[j]->position.y < (All[0]->position.y + All[0]->ActualHeight))) {
				All[0]->Health -= All[j]->Damage;
			}
		}
		if (!PlayerCheck && j < (int)All.size()) {
			if ((All[j]->position.x + All[j]->ActualWidth) < 0 || (All[j]->position.x > Curr->dimensions.x) || (All[j]->position.y > Curr->dimensions.y) || ((All[j]->position.y + All[j]->ActualHeight) < 0)){
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(All[j]);
			}
		}
	}
	return 0;
}

void Physics::FricTick(std::vector<Character*> All){
	for (int i = 0; i < (int)All.size(); i++) {
		BarrelCheck = dynamic_cast<Barrel*>(All[i]);
		if (!BarrelCheck) {
			if (All[i]->velocity.x == 0) {}
			else if (All[i]->velocity.x > 0 && (All[i]->bRunning && All[i]->bOnGround)) {
				All[i]->velocity.x -= 0.1f;
			}
			else if (All[i]->velocity.x < 0 && (All[i]->bRunning && All[i]->bOnGround)) {
				All[i]->velocity.x += 0.1f;
			}
		}
	}
}