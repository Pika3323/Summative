#pragma once

#include "Enemy.h"
#include "PlayState.h"

class Dankey : public Enemy{
public:
	bool Active;

	bool PlayerinSight;

	Dankey(Vector2D pos);

	void Run(Vector2D velocity);

	void Jump();
	
	void Die();

	void Tick(float delta);
protected:
	//SpriteSheet toss;
	//SpriteSheet still;
};