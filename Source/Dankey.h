#pragma once

#include "Enemy.h"
#include "PlayState.h"
#include "Barrel.h"

//Monkey that stands still and throws barrels
class Dankey : public Enemy{
public:
	//counts an interval between barrel throws
	int BarrelDelay;

	//Whether the player is in range
	bool PlayerinSight;

	Dankey(Vector2D pos);

	//Called when the character runs
	void Run(Vector2D velocity);

	//Called when the character jumps
	void Jump();
	
	//Called when the character dies
	void Die();

	//Called on every frame
	void Tick(float delta, std::vector<Character*> *Curr);

	//Called when the character collides with a block
	void BlockCollide(bool w, ECollisionDirection direction);

	//Called when the character collides with another character
	void Collide(Character* OtherCharacter);
};