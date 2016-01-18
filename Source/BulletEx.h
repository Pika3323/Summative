#pragma once

#include "Engine.h"
#include "SpriteSheet.h"
#include "Character.h"

//Explosion of a bullet
//UNUSED
class BulletEx : public Character{
public:
	void Run(Vector2D velocity);

	void Jump();

	void Tick(float delta, std::vector<Character*> *Curr);

	void Die();

	void Collide(Character* OtherCharacter);

	void BlockCollide(bool w, int CollisionDirection);

	BulletEx(Vector2D pos, ECharacterDirection d);
	
	//in public soley for deleting purposes and frame management
	SpriteSheet explode;
private:
};