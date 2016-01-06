#include "Physics.h"

Physics::Physics(Vector2D f){
	Gravforce = f;
}

void Physics::Register(Character* registrant){
	All.push_back(registrant);
	ColPos.push_back(Vector2D(0.f, 0.f));
}

void Physics::GravTick(){
	for (int i = 0; i < (int)All.size(); i++) {		//adding gravity to all characters registered
		if (!All[i]->bOnGround){
			All[i]->velocity.y = All[i]->velocity.y + Gravforce.y;	//could theoretically implement an x gravity if ever wanted to
		}
		if (All[i]->velocity.y >= 50) {
			All[i]->velocity.y = 50;
		}
	}
}

void Physics::ColTick(World* Curr){
	for (int j = 0; j < (int)All.size(); j++) {
		if (Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y) / 32)].bSpawned && All[j]->velocity.y < 0 && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 32)][int((All[j]->GetCharacterWorldPosition().y) / 32)].bCollision) {
			ColPos[j] = Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x) / 15)][int((All[j]->GetCharacterWorldPosition().y + 5) / 32)].position;
			All[j]->SetCharacterWorldPosition(Vector2D(All[j]->GetCharacterWorldPosition().x, ColPos[j].y));
			All[j]->velocity.y = 0;
		}
		for (int i = 33; i < 98; i += 32) {
			if (!static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 65) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 65) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {		//all possible x related collisions
				All[j]->velocity.x = -5.f;

		}
			else if (static_cast<bool>(All[j]->GetCharacterDirection()) && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 1) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[j]->GetCharacterWorldPosition().x + 65) / 32)][int((All[j]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {
				All[j]->velocity.x = 5.f;
			}
		}
	}
}

void Physics::FricTick(){
	for (int i = 0; i < (int)All.size(); i++){
		if (All[i]->velocity.x == 0) {}
		else if (All[i]->velocity.x > 0 && (All[i]->bRunning || All[i]->bOnGround)) {
			All[i]->velocity.x -= .5f;
		}
		else if (All[i]->velocity.x < 0 && (All[i]->bRunning || All[i]->bOnGround)) {
			All[i]->velocity.x += .5f;
		}
	}
}