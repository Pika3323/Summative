#pragma once

#include "Engine.h"
#include "Enemy.h"
#include "PlayState.h"

class Cinas : public Enemy{
public:

	Vector2D StartPosition;

	Cinas(Vector2D pos);

	void Run(Vector2D velocity);

	void Jump();

	void Die();

	void Tick(float delta, std::vector<Character*> *Curr);

	bool bCharacterLocked;

private:
};