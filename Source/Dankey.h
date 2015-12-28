#pragma once

#include "Enemy.h"

class Dankey : public Enemy{
public:
	bool Active;

	void Tick(float delta);

	Dankey(Vector2D pos);
protected:
	SpriteSheet toss;
	SpriteSheet still;
};