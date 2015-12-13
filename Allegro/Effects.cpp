#include "Effects.h"

Gravity::Gravity(Vector2D f){
	slot = 0;		//making slot zero when a gravity force is registered
	force = f;
}

int Gravity::Register(Character* registrant, bool onOff){
	All[slot] = registrant;		//function for registering character in next slot
	GonOff[slot] = onOff;
	slot++;
	return slot - 1;
}

void Gravity::Tick(){
	for (int i = 0; i < slot; i++) {		//adding gravity to all characters registered
		if (GonOff[i]){
			All[i]->position.y = All[i]->position.y + force.y;	//could theoretically implement an x gravity if ever wanted to
		}
	}
}