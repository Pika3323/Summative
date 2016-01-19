#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"

//Bullet fired by the player
//UNUSED
class Bullet : public Character {
public:

	void Tick(float delta, std::vector<Character*> *Curr);
	
	void Run(Vector2D velocity);

	void Die();

	void Jump();

	void Collide(Character* OtherCharacter);

	void BlockCollide(bool w, int CollisionDirection);

	Bullet(Vector2D pos, ECharacterDirection d);

private:
	SpriteSheet bullet;
};