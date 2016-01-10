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
	Vector2D ColPos;
	Character* TypeChecker;

	Physics();
	Physics(Vector2D f);	//setting the gravity first

	void GravTick(std::vector<Character*> All);	//applying force
	void FricTick(std::vector<Character*> All);	//Constant friction on any block at the moment
	int ColTick(class World* Curr, std::vector<Character*> All);		//collision conditions
private:
};
