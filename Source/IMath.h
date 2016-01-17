#pragma once
#include "Engine.h"

namespace IMath{
	bool InRange(float num, float min, float max);			//A few functions found to be useful throughout the game development

	float Clamp(float num, float min, float max);
}