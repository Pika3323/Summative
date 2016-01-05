#pragma once

#include "Engine.h"
#include "World.h"
#include "Character.h"
#include <vector>

class Physics{
public:
	Vector2D Gravforce;	//actual force exerted (dy)
	int slot;	//for holding slot in array of characters as they are registered
	//class Character* All[100];		//all character to be affected by gravity
	bool GonOff[100];
	Vector2D CollisionPos[100];
	std::vector<Character*> All;

	Physics();
	Physics(Vector2D f);	//setting the gravity first

	void Register(Character* registrant);	//registering characters and whether and not they are affected
	void GravTick();	//applying force
	void ColTick(class World* Curr, Character* charac);		//collision conditions

private:
};
