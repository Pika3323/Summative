#pragma once

#include "Enemy.h"

class Dankey : public Enemy{
public:
	void Tick(float delta);

	void Die();

	Dankey();
protected:
	SpriteSheet toss;
	SpriteSheet still;
};