#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"
#include "Bullet.h"

//Main player character (controlled by the player)
class Player : public Character{
public:
	//Whether the player has won
	bool PlayerWin;

	//Whether the player just shot
	bool ShotAlready;

	//Whether the palyer is shooting
	bool bShooting;

	//Called when the character runs
	void Run(Vector2D velocity);

	//Called when the character jumps
	void Jump();

	//Called every frame
	void Tick(float delta, std::vector<Character*> *Curr);

	//Called when the character dies
	void Die();

	//Called when the player wins
	void Win(Vector2D Start);

	//Called when the character collides with another character
	void Collide(Character* OtherCharacter);

	//Called when the character collides with a block
	void BlockCollide(bool w, ECollisionDirection direction);

	Player(int Height, int Width);
protected:
	SpriteSheet run;
	SpriteSheet fall;
	SpriteSheet still;
	SpriteSheet shoot;
};