#pragma once

#include "Engine.h"

class Character{
public:
	//essentials of class
	Vector2D position;
	Vector2D velocity;
	Vector2D delta;
	ALLEGRO_BITMAP *spritesheet;
	int ActualWidth;
	int ActualHeight;
	char animation;
	int maxfram;
	int curfram;
	int delay;
	int framcount;
	int gravSlot;
	bool moving;
	bool flipped;

	//constructors
	Character(){}
	Character(Vector2D xy, int width, int height);

	//event handlers (i idle, r run, s stop, j jump)
	void DoEv(char CharacterEv);
	void EvHandle();
	void Animate(bool flipped);
private:
};