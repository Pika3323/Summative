#pragma once

#include "Engine.h"

//Represents the direction in which the character is facing
enum class ECharacterDirection{
	R_Right,
	R_Left
};

class Character{
public:
	//The direction that the character is facing
	ECharacterDirection direction;

	//The character's instantaneous velocity
	Vector2D velocity;

	//The position of the character
	Vector2D position;

	//The gravity effect slot
	int gravSlot;

	//Whether the character is running
	bool bRunning;

	//Whether the character has been flipped
	bool bFlipped;

	//Whether the character is touching the ground or is in the air
	bool bOnGround;

	//The actual width of the character
	int ActualWidth;

	//The actual height of the character
	int ActualHeight;

	//Default constructor
	Character(){ direction = ECharacterDirection::R_Right; }
	
	//Character Constructor
	Character(Vector2D xy, int width, int height);

	//Called while the character is running
	virtual void Run(Vector2D velocity) = 0;

	//Called when the character jumps
	virtual void Jump() = 0;

	//Called on every frame
	virtual void Tick(float delta, std::vector<Character*> *Curr) = 0;

	//Called when the character dies
	virtual void Die() = 0;
	
	//Sets the position of the character
	void SetCharacterWorldPosition(Vector2D NewV);

	//Returns the position of the character
	Vector2D GetCharacterWorldPosition();

	//Set the direction in which the character is facing
	void SetCharacterDirection(ECharacterDirection NewDirection);
	
	//Return the direction in which the character is facing
	ECharacterDirection GetCharacterDirection();

	//Draws the character to the screen
	void Draw();

	//Character destructor
	~Character();
protected:
	//The overall texture of the character which is drawn to the screen
	ALLEGRO_BITMAP* texture;

};