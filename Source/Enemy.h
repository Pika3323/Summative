#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"

class Enemy : public Character{
public:
	int Damage;

	virtual void Run(Vector2D velocity);

	virtual void Jump();

	virtual void Tick(float delta);

	virtual void Die();

	Enemy();
protected:
	SpriteSheet run;
	SpriteSheet fall;
	SpriteSheet still;
	SpriteSheet attack;

};