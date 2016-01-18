#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"
#include "Player.h"

//List of all types of enemies
enum class EnemyType{
	E_Cinas,
	E_Dankey,
	E_Yash,
	E_Barrel
};

//Abstract base class of all enemies
class Enemy : public Character{
public:
	//The enemy's type 
	EnemyType Type; 

	//Called when the character runs
	virtual void Run(Vector2D velocity) = 0;

	//Called when the character jumps
	virtual void Jump() = 0;

	//Called on every frame
	virtual void Tick(float delta, std::vector<Character*> *Curr) = 0;

	//Called when the character dies
	virtual void Die() = 0;

	//Called when the character collides with another character
	virtual void Collide(Character* OtherCharacter) = 0;

	//Called when the character collides with a block
	virtual void BlockCollide(bool w, ECollisionDirection direction) = 0;

	Enemy();
protected:
	//Running spritesheet
	SpriteSheet run;
	
	//Attacking spritesheet
	SpriteSheet attack;
	
	//Falling spritesheet
	SpriteSheet fall;
	
	//Standing still spritesheet
	SpriteSheet still;
};