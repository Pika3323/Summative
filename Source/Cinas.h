#pragma once

#include "Engine.h"
#include "Enemy.h"
#include "PlayState.h"

//Red hedgehog that chases the player around the level
class Cinas : public Enemy{
public:
	Cinas(Vector2D pos);

	//Called when the character runs
	void Run(Vector2D velocity);

	//Called when the character jumps
	void Jump();

	//Called when the character dies
	void Die();
	
	//Called every frame
	void Tick(float delta, std::vector<Character*> *Curr);

	//Called when the character collides with a block
	void BlockCollide(bool w, ECollisionDirection direction);

	//Called when the character collides with another character
	void Collide(Character* OtherCharacter);

	//Whether this enemy has spotted the character
	bool bCharacterLocked;

private:
};