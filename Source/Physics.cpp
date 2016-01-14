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
			BoundingBox B = All[i]->CollisionBounds;
			if ((All[i]->CollisionBounds.position.x + All[i]->CollisionBounds.size.x) >= (B.position.x)
				&& (All[i]->CollisionBounds.position.x) <= (B.position.x + B.size.x)
				&& (All[i]->CollisionBounds.position.y + All[i]->CollisionBounds.size.y) >= (B.position.y)
				&& (All[i]->CollisionBounds.position.y) <= (B.position.y + B.size.y)){

			}
		}


		All[i]->position += All[i]->velocity;
	}


}