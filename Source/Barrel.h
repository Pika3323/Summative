#pragma once

#include "Engine.h"
#include "Enemy.h"
#include "PlayState.h"

//Barrel character which is thrown by Dankey
class Barrel : public Enemy{
public:
	//Called while the character is running
	void Run(Vector2D velocity);

	//Called when the character jumps
	void Jump();

	//Called on every frame
	void Tick(float delta, std::vector<Character*> *Curr);

	//Called when the character dies
	void Die();

	//Called when the character collides with another character
	void Collide(Character* OtherCharacter);

	//Called when the character collides with a block
	void BlockCollide(bool w, ECollisionDirection direction);

	Barrel(ECharacterDirection d, Vector2D pos);

private:
	//The spritesheet for the rolling animation
	SpriteSheet Roll;
};