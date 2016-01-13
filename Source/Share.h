#pragma once

#include "Engine.h"

//Put all declarations for shared variables here!
struct Share{
	bool bLoadingLevel;
	char LoadLevelName[64];
	char SaveLevelName[64];
	int id;
};