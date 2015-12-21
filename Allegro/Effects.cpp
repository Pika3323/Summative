#include "Effects.h"


Effects::Effects(Vector2D f){
	slot = 0;		//making slot zero when a gravity force is registered
	Gravforce = f;
}

int Effects::Register(Character* registrant, bool onOff){
	All[slot] = registrant;		//function for registering character in next slot
	GonOff[slot] = onOff;
	slot++;
	return slot - 1;
}

void Effects::GravTick(){
	for (int i = 0; i < slot; i++) {		//adding gravity to all characters registered
		if (GonOff[i]){
			All[i]->velocity.y = All[i]->velocity.y + Gravforce.y;	//could theoretically implement an x gravity if ever wanted to
		}
		if (All[i]->velocity.y >= 50) {
			All[i]->velocity.y = 50;
		}
	}
}

void Effects::ColTick(World* Curr, Character &charac){
	for (int i = 0; i < 2; i++) {		//all registered characters
		if (!charac.flipped && Curr->Blocks[(int)((charac.position.x + 65) / 32)][int((charac.position.y + 33) / 32)].bSpawned){		//all possible x related collisions
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}
		else if (!charac.flipped && Curr->Blocks[(int)((charac.position.x + 65) / 32)][int((charac.position.y + 65) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}
		else if (!charac.flipped && Curr->Blocks[(int)((charac.position.x + 65) / 32)][int((charac.position.y + 97) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}

		else if (charac.flipped && Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y + 33) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x + 33) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}
		else if (charac.flipped && Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y + 65) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x + 33) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}
		else if (charac.flipped && Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y + 97) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x + 33) / 32)][int((charac.position.y) / 32)].position;
			charac.position.x = CollisionPos[charac.gravSlot].x;
		}
		if (Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y) / 32)].bSpawned && charac.velocity.y < 0){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.position.x) / 32)][int((charac.position.y + 5) / 32)].position;
			charac.position.y = CollisionPos[charac.gravSlot].y;
			charac.velocity.y = 0;
		}
	}
}