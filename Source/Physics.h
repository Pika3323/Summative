#pragma once

#include "Engine.h"
#include "World.h"
#include "Character.h"
#include "Player.h"
#include "Dankey.h"
#include "Bullet.h"
#include "BulletEx.h"

class Physics{
public:
	Vector2D Gravforce;	//actual force exerted (dy)
	bool Deleted;

	Physics();
	Physics(Vector2D f);	//setting the gravity first

	void Tick(std::vector<Character*> &All);	//applying force
private:
	bool OnScreen(Character* C);
	bool HitBlock(Character* C);
};
