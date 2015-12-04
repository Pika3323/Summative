#pragma once


#include <math.h>

struct Vector2D{
	//main components of class
	float x;
	float y;

public:
	//constructors
	Vector2D() {}
	Vector2D(float inX, float inY);
	Vector2D(const Vector2D &V);

	//operators
	Vector2D operator+(const Vector2D &V);
	Vector2D operator-(const Vector2D &V);
	Vector2D operator*(float Scale);
	Vector2D operator/(float Scale);
	Vector2D operator+=(const Vector2D &V);
	Vector2D operator-=(const Vector2D &V);

	bool operator==(const Vector2D &V);

	float operator|(const Vector2D &V);	//dot-product
	float operator^(const Vector2D &V);	//cross-product

	//functions
	float Magnitude();	//returns the magnitude/length of the vector
protected:

};

