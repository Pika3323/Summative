#pragma once

#include "Engine.h"
#include "World.h"
#include "Character.h"
#include "Player.h"
#include <vector>
#include "Dankey.h"

class Physics{
public:
	Vector2D Gravforce;	//actual force exerted (dy)
	std::vector<Vector2D> ColPos;		//vector for collision postions
	std::vector<Character*> All;		//stores characters to be affected by physics
	Dankey *dColptr;		//for checkiing the All types


	Physics();
	Physics(Vector2D f);	//setting the gravity first

	void Register(Character* registrant);	//registering characters and whether and not they are affected
	void GravTick();	//applying force
	void FricTick();	//Constant friction on any block at the moment
	int ColTick(class World* Curr);		//collision conditions

private:
};
