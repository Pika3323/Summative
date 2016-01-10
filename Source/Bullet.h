#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"

class Bullet : public Character {
public:

	void Tick(float delta, std::vector<Character*> *Curr);
	
	void Run(Vector2D velocity);

	void Die();

	void Jump();

	Bullet(Vector2D pos);

private:
	SpriteSheet bullet;
};