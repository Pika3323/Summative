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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!For the love of god CLEAN THIS UP PLS!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Effects::ColTick(World* Curr, Character &charac){
		if (Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].bSpawned && charac.velocity.y < 0) {
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x) / 15)][int((charac.GetCharacterWorldPosition().y + 5) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(charac.GetCharacterWorldPosition().x, CollisionPos[charac.gravSlot].y));
			charac.velocity.y = 0;
		}
		if (!static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 65) / 32)][int((charac.GetCharacterWorldPosition().y + 33) / 32)].bSpawned){		//all possible x related collisions
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}
		else if (!static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 65) / 32)][int((charac.GetCharacterWorldPosition().y + 65) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}
		else if (!static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 65) / 32)][int((charac.GetCharacterWorldPosition().y + 97) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}
		else if (static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 1) / 32)][int((charac.GetCharacterWorldPosition().y + 33) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 15) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}
		else if (static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 1) / 32)][int((charac.GetCharacterWorldPosition().y + 65) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 15) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}
		else if (static_cast<bool>(charac.GetCharacterDirection()) && Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 1) / 32)][int((charac.GetCharacterWorldPosition().y + 97) / 32)].bSpawned){
			CollisionPos[charac.gravSlot] = Curr->Blocks[(int)((charac.GetCharacterWorldPosition().x + 15) / 32)][int((charac.GetCharacterWorldPosition().y) / 32)].position;
			charac.SetCharacterWorldPosition(Vector2D(CollisionPos[charac.gravSlot].x, charac.GetCharacterWorldPosition().y));
		}

}