#pragma once
#include "Engine.h"

//Contains a set of mathematical functions
namespace IMath{
	//Returns true if num is between min and max
	bool InRange(float num, float min, float max);

	//Clamps the value of num between min and max
	float Clamp(float num, float min, float max);
}