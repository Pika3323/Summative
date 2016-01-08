#pragma once

#include "Engine.h"
#include "Enemy.h"
#include "PlayState.h"

class Barrel : public Enemy{
public:
	ECharacterDirection RollDirection;

	void Run(Vector2D velocity);

	void Jump();

	void Tick(float delta);

	void Die();

	Barrel(ECharacterDirection d, Vector2D pos);

private:
	SpriteSheet Roll;
};