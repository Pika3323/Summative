#include "Vector2D.h"

//Constructors
Vector2D::Vector2D(float inX, float inY){
	x = inX;
	y = inY;
}
Vector2D::Vector2D(const Vector2D &V){
	x = V.x;
	y = V.y;
}

//Operators
Vector2D Vector2D::operator+(const Vector2D &V){
	return Vector2D(x + V.x, y + V.y);
}

Vector2D Vector2D::operator-(const Vector2D &V){
	return Vector2D(x - V.x, y - V.y);
}

Vector2D Vector2D::operator*(float Scale){
	return Vector2D(x * Scale, y * Scale);
}

Vector2D Vector2D::operator/(float Scale){
	return Vector2D(x / Scale, y / Scale);
}

Vector2D Vector2D::operator+=(const Vector2D &V){
	x += V.x;
	y += V.y;
	return *this;
}
Vector2D Vector2D::operator-=(const Vector2D &V){
	x -= V.x;
	y -= V.y;
	return *this;
}

bool Vector2D::operator==(const Vector2D &V){
	return x == V.x && y == V.y;
}

//dot-product
float Vector2D::operator|(const Vector2D &V){
	return x * V.x + y * V.y;
}

//cross-product
float Vector2D::operator^(const Vector2D &V){
	return x*V.y - y*V.x;
}

//Functions
float Vector2D::Magnitude(){
	return sqrt(x * x + y * y);
}