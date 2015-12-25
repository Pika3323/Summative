#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"

class Enemy : public Character{
public:
	void Run(Vector2D velocity);

	void Jump();

	void Tick(float delta);

	void Die();

	Enemy();
protected:
	SpriteSheet run;
	SpriteSheet fall;
	SpriteSheet still;
};