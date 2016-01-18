#include "Physics.h"

Physics::Physics(Vector2D f){
	Gravforce = f;
}

void Physics::Tick(std::vector<Character*> &All){
	for (int i = 0; i < (int)All.size(); i++){
		if (!All[i]->bOnGround){			//if the character is not on the ground, it is affected by gravity
			All[i]->velocity += Gravforce;
		}
		if (All[i]->velocity.y > 50.f){			//terminal velocity for this game
			All[i]->velocity.y = 50.f;
		}


		for (int j = 0; j < (int)All.size(); j++){
			if (j == i){				//cant have the character evluating against itself
				if (++j >= (int)All.size()){
					break;
				}
			}
			if (Physics::OnScreen(All[i]) && Physics::OnScreen(All[j])) {
				if ((All[i]->position.x + All[i]->CollisionBounds.position.x + All[i]->CollisionBounds.size.x) >= (All[j]->position.x + All[j]->CollisionBounds.position.x)		//magic bounding box collision
					&& (All[i]->position.x + All[i]->CollisionBounds.position.x) <= (All[j]->position.x + All[j]->CollisionBounds.position.x + All[j]->CollisionBounds.size.x)	//with allegro
					&& (All[i]->position.y + All[i]->CollisionBounds.position.y + All[i]->CollisionBounds.size.y) >= (All[j]->position.y + All[j]->CollisionBounds.position.y)
					&& (All[i]->position.y + All[i]->CollisionBounds.position.y) <= (All[j]->position.y + All[j]->CollisionBounds.position.y + All[j]->CollisionBounds.size.y)){
					All[i]->Collide(All[j]);		//call both character's collide function
					All[j]->Collide(All[i]);
				}
			}
		}

		if (!Physics::HitBlock(All[i])){		//check if the character has hit any blocks)
			All[i]->position += All[i]->velocity;		//add all of the character's velocities to their position
		
		}
	}
}

bool Physics::OnScreen(Character* C){
	if (C->position.x > (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1) &&					//checking if the character is on the screen
		C->position.x < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.x * -1 + GEngine->GetDisplayWidth()) &&
		C->position.y >(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1) &&
		C->position.y < (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->offset.y * -1 + GEngine->GetDisplayHeight())){
		return true;
	}
	else {
		return false;
	}
}

bool Physics::HitBlock(Character* C){
	Deleted = false;
	bool win = false;
	World* W = dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld;
	/*All of these collisions are block based, meaning that we take the character position and add its hitbox parameters. Then, we take that value and divide by the gridsize
	to locate the block that is at his position (we find the array number that is at his position). Right collision (0) means he has colllided with a block on his right side.
	Left Collision (1) means he has collided with a block on his left side. For both 0 and 1, the number of blocks that one character can hit is based on its hitbox height.
	Top collision (2) means that the character has hit a block above its hitbox, meaning it will come back down. DownStay (3) means that the character should stay on the ground,
	as there is a spawned collidable block under him. DownStop (4), means he should stop colliding with the block underneath him as there is no block or there is a block, but it 
	is not a collidable block. This means he will fall. This will also check if the character has gone off the screen (deleting it).
	*/


	//Bottom Collision, setting positions. 
	if (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
		win = true;
	if (!C->bOnGround && (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].bSpawned &&
		W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - 1) / (W->gridSize))].bCollision)){
		C->SetCharacterWorldPosition(Vector2D(C->position.x, W->Blocks[(int)(C->position.x / W->gridSize)][(int)(C->position.y / W->gridSize)].position.y));
		C->BlockCollide(win, ECollisionDirection::DownStay);
	}
	win = false;

	//Bottom fall, making characters fall through
	if (C->bOnGround && W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bSpawned &&
		!W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bCollision){
		C->BlockCollide(win, ECollisionDirection::DownStop);
	}

	if (!W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y + 1) / (W->gridSize))].bSpawned){
		C->BlockCollide(win, ECollisionDirection::DownStop);
	}

	//Top side Collision
	if (W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].type == EBlockType::B_FinishFlag)
		win = true;
	if ((W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].bSpawned &&
		W->Blocks[(int)((C->position.x + C->CollisionBounds.position.x + (C->CollisionBounds.size.x / 2)) / (W->gridSize))][(int)((C->position.y + C->CollisionBounds.position.y - 10) / (W->gridSize))].bCollision)){
		C->SetCharacterWorldPosition(Vector2D(C->position.x, W->Blocks[(int)(C->position.x / W->gridSize)][(int)(C->position.y / W->gridSize)].position.y));
		C->BlockCollide(win, ECollisionDirection::Top);
	}
	win = false;

	int j = ceil(C->CollisionBounds.size.y / W->gridSize);

	//Right/Left side collision
	for (int i = 0; i < j; i++){
		if (!static_cast<int>(C->direction) && W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + C->CollisionBounds.size.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
			win = true;
		if (!static_cast<int>(C->direction) && (W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + C->CollisionBounds.size.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bSpawned &&
			W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x + C->CollisionBounds.size.x + 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bCollision)){
			C->BlockCollide(win, ECollisionDirection::Right);
			if (dynamic_cast<Barrel*>(C)){
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(C);
				Deleted = true;
			}
		}
		win = false;
		if (static_cast<int>(C->direction) && W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].type == EBlockType::B_FinishFlag)
			win = true;
		if (static_cast<int>(C->direction) && (W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bSpawned &&
			W->Blocks[(int)(C->position.x + C->CollisionBounds.position.x - 1) / (W->gridSize)][(int)((C->position.y + C->CollisionBounds.position.y + C->CollisionBounds.size.y - (i * 32) - 1) / (W->gridSize))].bCollision)){
			C->BlockCollide(win, ECollisionDirection::Left);
			if (dynamic_cast<Barrel*>(C)){
				dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(C);
				Deleted = true;
			}
		}
		win = false;
	}

	if (!Deleted && !dynamic_cast<Player*>(C)){
		if (C->position.x < 0 || C->position.x + C->ActualWidth >(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->dimensions.x) || C->position.y > (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->dimensions.y) || C->position.y + C->ActualHeight < 0){
			dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->DestroyCharacter(C);
			Deleted = true;
		}
	}
	return Deleted;
}