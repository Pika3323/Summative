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
			All[i]->position.y = All[i]->position.y + Gravforce.y;	//could theoretically implement an x gravity if ever wanted to
		}
	}
}

void Effects::ColTick(World* Curr, Character charac){
	for (int i = 0; i < slot; i++) {		//all registered characters
		if (Curr->Blocks[(int)((charac.position.x) / 32)][int(charac.position.y / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = charac.position;
			charac.position = CollisionPos[charac.gravSlot];
		}
	}
}