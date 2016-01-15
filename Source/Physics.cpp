#include "Physics.h"

Physics::Physics(Vector2D f){
	Gravforce = f;
}

void Physics::Tick(std::vector<Character*> &All){
	for (int i = 0; i < (int)All.size(); i++){
		if (!All[i]->bOnGround){
			All[i]->velocity += Gravforce;
		}
		if (All[i]->velocity.y > 50){
			All[i]->velocity.y = 50;
		}


		for (int j = 0; j < (int)All.size(); j++){
			if (j == i)
				j++;
			if (Physics::OnScreen(All[i]) && Physics::OnScreen(All[j])) {
				if ((All[i]->position.x + All[i]->CollisionBounds.position.x + All[i]->CollisionBounds.size.x) >= (All[j]->position.x + All[j]->CollisionBounds.position.x)
					&& (All[i]->position.x + All[i]->CollisionBounds.position.x) <= (All[j]->position.x + All[j]->CollisionBounds.position.x + All[j]->CollisionBounds.size.x)
					&& (All[i]->position.y + All[i]->CollisionBounds.position.y + All[i]->CollisionBounds.size.y) >= (All[j]->position.y + All[j]->CollisionBounds.position.y)
					&& (All[i]->position.y + All[i]->CollisionBounds.position.y) <= (All[j]->position.y + All[j]->CollisionBounds.position.y + All[j]->CollisionBounds.size.y)){
						All[i]->Collide(All[j]);
						All[j]->Collide(All[i]);
				}
			}
		}

		Physics::HitBlock(All[i]);
		Physics::Fall(All[i]);

		All[i]->position += All[i]->velocity;
	}
}

bool Physics::OnScreen(Character* C){
	return C->position.x > (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1) &&
		C->position.x < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1 + GEngine->GetDisplayWidth) &&
		C->position.y >(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1) &&
		C->position.y < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1 + GEngine->GetDisplayHeight);
}

bool Physics::HitBlock(Character* C){
	World* W = dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld;

	/*if ((W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + 1) / (W->gridSize)][(int)(C->position.y + C->CollisionBounds.position.y) / (W->gridSize)].bSpawned && 
		W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + 1) / (W->gridSize)][(int)(C->position.y + C->CollisionBounds.position.y) / (W->gridSize)].bCollision) ||
		W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + 1) / (W->gridSize)][(int)(C->position.y + C->CollisionBounds.position.y + 32) / (W->gridSize)].bSpawned &&
		W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + 1) / (W->gridSize)][(int)(C->position.y + C->CollisionBounds.position.y + 32) / (W->gridSize)].bCollision) ||*/

}

bool Physics::Fall(Character *C){

}