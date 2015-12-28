#pragma once

#include "Enemy.h"
#include "Player.h"
#include "IMath.h"

class Dankey : public Enemy{
public:
	bool Active;

	bool PlayerinSight;

	Dankey(Vector2D pos);

	void Run(Vector2D velocity);

	void Jump();
	
	void Die();

	void Tick(float delta, Player* player);
protected:
	SpriteSheet toss;
	SpriteSheet still;
};