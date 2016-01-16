#pragma once

#include "Enemy.h"
#include "PlayState.h"
#include "Barrel.h"

class Dankey : public Enemy{
public:

	int BarrelDelay;

	bool PlayerinSight;

	Dankey(Vector2D pos);

	void Run(Vector2D velocity);

	void Jump();
	
	void Die();

	void Tick(float delta, std::vector<Character*> *Curr);

	void BlockCollide(bool w, int CollisionDirection);

	void Collide(Character* OtherCharacter);
protected:
};