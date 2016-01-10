#pragma once

#include "Engine.h"
#include "SpriteSheet.h"
#include "Character.h"

class BulletEx : public Character{
public:
	void Run(Vector2D velocity) = 0;

	//Called when the character jumps
	 void Jump() = 0;

	//Called on every frame
	void Tick(float delta, std::vector<Character*> *Curr) = 0;

	//Called when the character dies
	void Die() = 0;

	BulletEx(Vector2D pos);
	
	//in public soley for deleting purposes and frame management
	SpriteSheet explode;
private:
};