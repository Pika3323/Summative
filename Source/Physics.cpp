#include "Physics.h"

Physics::Physics(Vector2D f){
	slot = 0;		//making slot zero when a gravity force is registered
	Gravforce = f;
}

void Physics::Register(Character* registrant){
	All.push_back(registrant);
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

void Physics::ColTick(World* Curr, Character* charac){
	for (int i = 0; i < (int)All.size(); i++) {
		if (Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x) / 32)][int((All[i]->GetCharacterWorldPosition().y) / 32)].bSpawned && All[i]->velocity.y < 0 && Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x) / 32)][int((All[i]->GetCharacterWorldPosition().y) / 32)].bCollision) {
			CollisionPos[All[i]->gravSlot] = Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x) / 15)][int((All[i]->GetCharacterWorldPosition().y + 5) / 32)].position;
			All[i]->SetCharacterWorldPosition(Vector2D(All[i]->GetCharacterWorldPosition().x, CollisionPos[All[i]->gravSlot].y));
			All[i]->velocity.y = 0;
		}
		for (int i = 33; i < 98; i += 32) {
			if (!static_cast<bool>(All[i]->GetCharacterDirection()) && Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x + 65) / 32)][int((All[i]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x + 65) / 32)][int((All[i]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {		//all possible x related collisions
				CollisionPos[All[i]->gravSlot] = Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x) / 32)][int((All[i]->GetCharacterWorldPosition().y) / 32)].position;
				All[i]->SetCharacterWorldPosition(CollisionPos[All[i]->gravSlot]);
			}
			else if (static_cast<bool>(All[i]->GetCharacterDirection()) && Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x + 1) / 32)][int((All[i]->GetCharacterWorldPosition().y + i) / 32)].bSpawned && Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x + 65) / 32)][int((All[i]->GetCharacterWorldPosition().y + i) / 32)].bCollision) {
				CollisionPos[All[i]->gravSlot] = Curr->Blocks[(int)((All[i]->GetCharacterWorldPosition().x + 30) / 32)][int((All[i]->GetCharacterWorldPosition().y) / 32)].position;
				All[i]->SetCharacterWorldPosition(CollisionPos[All[i]->gravSlot]);
			}
		}
	}
}