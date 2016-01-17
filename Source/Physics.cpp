#include "Physics.h"

Physics::Physics(Vector2D f){
	Gravforce = f;
}

void Physics::Tick(std::vector<Character*> &All){
	for (int i = 0; i < (int)All.size(); i++){
		if (!All[i]->bOnGround){
			All[i]->velocity += Gravforce;
		}
		if (All[i]->velocity.y > 50.f){
			All[i]->velocity.y = 50.f;
		}


		for (int j = 0; j < (int)All.size(); j++){
			if (j == i){
				if (++j >= (int)All.size()){
					break;
				}
			}
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
		All[i]->position += All[i]->velocity;
	}
}

bool Physics::OnScreen(Character* C){
	if (C->position.x > (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1) &&
		C->position.x < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1 + GEngine->GetDisplayWidth()) &&
		C->position.y >(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1) &&
		C->position.y < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1 + GEngine->GetDisplayHeight())){
		return true;
	}
	else {
		return false;
	}
}

void Physics::HitBlock(Character* C){
	bool win = false;
	World* W = dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld;

	//Bottom Collision, setting positions
	if (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
		win = true;
	if (!C->bOnGround && (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].bSpawned &&
		W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].bCollision)){
		C->SetCharacterWorldPosition(Vector2D(C->position.x, W->Blocks[(int)(C->position.x / W->gridSize)][(int)(C->position.y / W->gridSize)].position.y));
		C->BlockCollide(win, 3);
	}
	win = false;

	//Bottom fall, making characters fall through
	if (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bSpawned &&
		!W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bCollision){
		C->BlockCollide(win, 4);
	}

	if (!W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bSpawned){
		C->BlockCollide(win, 4);
	}

	//Top side Collision
	if (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].type == EBlockType::B_FinishFlag)
		win = true;
	if ((W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].bSpawned &&
		W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].bCollision)){
		C->SetCharacterWorldPosition(Vector2D(C->position.x, W->Blocks[(int)(C->position.x / W->gridSize)][(int)(C->position.y / W->gridSize)].position.y));
		C->BlockCollide(win, 2);
	}
	win = false;

	int j = ceil(C->CollisionBounds.size.y / W->gridSize);

	//Right/Left side collision
	for (int i = 0; i < j; i++){
		if (!static_cast<int>(C->direction) && W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - ((i + 1) * 32) - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
			win = true;
		if (!static_cast<int>(C->direction) && (W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + C->CollisionBounds.size.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bSpawned &&
			W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + C->CollisionBounds.size.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - ((i + 1) * 32) - 1) / (W->gridSize))].bCollision)){
			C->BlockCollide(win, 0);
		}
		if (static_cast<int>(C->direction) && W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
			win = true;
		if (static_cast<int>(C->direction) && (W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bSpawned &&
			W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bCollision)){
			C->BlockCollide(win, 1);
		}
		win = false;
	}
}