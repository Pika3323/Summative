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

	//Adds two vectors
	Vector2D operator+(const Vector2D &V);

	//Subtracts two vectors
	Vector2D operator-(const Vector2D &V);

	//Multiplies a vector by a scalar value
	Vector2D operator*(float Scale);

	//Divides a vector by a scalar value
	Vector2D operator/(float Scale);

	Vector2D operator+=(const Vector2D &V);
	Vector2D operator-=(const Vector2D &V);
	Vector2D operator*=(float Scale);
	Vector2D operator/=(float Scale);

	bool operator>(const Vector2D &V);
	bool operator<(const Vector2D &V);
	bool operator>=(const Vector2D &V);
	bool operator<=(const Vector2D &V);

	bool operator==(const Vector2D &V);
	bool operator!=(const Vector2D &V);

	float operator|(const Vector2D &V);	//dot-product
	float operator^(const Vector2D &V);	//cross-product

	//returns the magnitude/length of the vector
	float Magnitude();	
protected:

};

