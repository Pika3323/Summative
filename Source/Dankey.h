#pragma once

#include "Enemy.h"
#include "Player.h"
#include "IMath.h"
#include "World.h"

class Dankey : public Enemy{
public:
	bool Active;

	bool PlayerinSight;

	Dankey(Vector2D pos);

	void Run(Vector2D velocity);

	void Jump();
	
	void Die();

	void Tick(float delta, Player* player, class World* Current);
protected:
	SpriteSheet toss;
	SpriteSheet still;
};