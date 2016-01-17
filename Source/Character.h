#pragma once

#include "Engine.h"

//Represents the direction in which the character is facing
enum class ECharacterDirection{
	R_Right,
	R_Left
};

struct BoundingBox{
	//Bounding box's position RELATIVE TO THE CHARACTER
	Vector2D position;

	//Size of the bounding box
	Vector2D size;
};

class Character{
public:
	//Amount of damage that can be dealt by the character
	float Damage;

	//Character's health
	float Health;

	//The direction that the character is facing
	ECharacterDirection direction;

	//Collision bounds for the character
	BoundingBox CollisionBounds;

	//The character's instantaneous velocity
	Vector2D velocity;

	//The position of the character
	Vector2D position;

	//Whether the character is running
	bool bRunning;

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

	//Called when the character collides with another character
	virtual void Collide(Character* OtherCharacter) = 0;

	//Called when the character collides with a block  (Collision Direction = 0 for right, 1 for left, 2 for up,  3 for down stay, 4 for down stop)
	virtual void BlockCollide(bool w , ECollisionDirection direction) = 0;
	
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

	//Sets up collision bounds for the character
	void SetupCharacterCollision(Vector2D position, Vector2D size);

	//Character destructor
	~Character();
protected:
	//The overall texture of the character which is drawn to the screen
	ALLEGRO_BITMAP* texture;

};