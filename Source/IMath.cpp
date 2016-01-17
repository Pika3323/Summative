#include "IMath.h"

bool IMath::InRange(float num, float min, float max){
	return num > min && num < max;			//if it is within the given range, return true
}

float IMath::Clamp(float num, float min, float max){
	if (num > max) {			//for keeping a number within a certain range
		num = max;
	}

	if (num < min) {
		num = min;
	}

	return num;
}