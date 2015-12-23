#pragma once

#include "Engine.h"

enum class ECharacterDirection{
	R_Right,
	R_Left
};

class Character{
public:
	//essentials of class
	Vector2D position;
	Vector2D velocity;

	//constructors
	Character(){}
	Character(Vector2D xy, int width, int height);

	//event handlers (i idle, r run, s stop, j jump)
	virtual void Run(Vector2D velocity) = 0;
	virtual void Jump() = 0;
	virtual void Tick(float delta) = 0;
	virtual void Die() = 0;

	void DoEv(char CharacterEv);
	void EvHandle();
	void Animate(bool flipped);
	void shutdown();

	void SetCharacterDirection(ECharacterDirection NewDirection);
	void Draw();

	~Character();

protected:
	ALLEGRO_BITMAP* texture;

	ALLEGRO_BITMAP *spritesheet;
	ALLEGRO_BITMAP *running;
	ALLEGRO_BITMAP *idle;
	ALLEGRO_BITMAP *falling;

	int ActualWidth;
	int ActualHeight;
	char animation;
	int maxfram;
	int curfram;
	int delay;
	int framcount;
	int gravSlot;
	
	bool bMoving;
	bool bFlipped;
	bool bOnGround;
private:
	ECharacterDirection direction;
};