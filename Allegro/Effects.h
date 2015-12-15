#pragma once

#include "Engine.h"
#include "Character.h"

class Gravity{
public:
	Vector2D force;	//actual force exerted (dy)
	int slot;	//for holding slot in array of characters as they are registered
	class Character* All[100];		//all character to be affected by gravity
	bool GonOff[100];


	Gravity();
	Gravity(Vector2D f);	//setting the gravity first

	int Register(Character* registrant, bool onOff);	//registering characters and whether and not they are affected
	void Tick();	//actually applying force
private:
};
