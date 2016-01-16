#include "IMath.h"

bool IMath::InRange(float num, float min, float max){
	return num > min && num < max;
}

float IMath::Clamp(float num, float min, float max){
	if (num > max) {
		num = max;
	}

	if (num < min) {
		num = min;
	}

	return num;
}