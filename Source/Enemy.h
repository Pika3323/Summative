#pragma once

#include "Engine.h"
#include "Character.h"
#include "SpriteSheet.h"
#include "Player.h"

enum class EnemyType{
	E_Cinas,
	E_Dankey,
	E_Yash,
	E_Barrel
};

class Enemy : public Character{
public:
	EnemyType Type; //type of monster it is

	bool Active;

	virtual void Run(Vector2D velocity) = 0;

	virtual void Jump() = 0;

	virtual void Tick(float delta, std::vector<Character*> *Curr) = 0;

	virtual void Die() = 0;

	virtual void Collide(Character* OtherCharacter) = 0;

	virtual void BlockCollide(bool w, int CollisionDirection) = 0;

	Enemy();
protected:
	SpriteSheet run;
	SpriteSheet attack;
	SpriteSheet fall;
	SpriteSheet still;
};