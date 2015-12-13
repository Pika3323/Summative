#include "Effects.h"

Gravity::Gravity(Vector2D f){
	slot = 0;		//making slot zero when a gravity force is registered
	force = f;
}

void Gravity::Register(Character registrant, bool onOff){
	All[slot] = registrant;		//function for registering character in next slot
	GonOff[slot] = onOff;
	slot++;
}

void Gravity::Tick(){
	for (int i = 0; i < (slot + 1); i++) {		//adding gravity to all character registered
		if (GonOff[i]){
			All[i].position.y = All[i].position.y + force.y;	//could theoretically implement an x gravity if ever wanted to
		}
	}
}