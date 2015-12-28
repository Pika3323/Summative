#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"
#include "Player.h"

enum class EnemyType{
	E_Cinas,
	E_Dankey,
	E_Yash
};

class Enemy : public Character{
public:
	int Damage;

	EnemyType Type; //type of monster it is

	bool Active;

	virtual void Run(Vector2D velocity) = 0;

	virtual void Jump() = 0;

	void Tick(float delta, Player* player);

	virtual void Die();

	Enemy();
protected:
	SpriteSheet run;
	SpriteSheet fall;
	SpriteSheet still;
	SpriteSheet attack;
};