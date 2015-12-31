#pragma once

//Allegro headers
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>

//Standard headers
#include <stdio.h>
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
#endif
#include <stdlib.h>
#ifdef _DEBUG
	#include <crtdbg.h>
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <vector>

//Core Engine components
#include "Vector2D.h"		//Vector header, including some vector math
#include "IMath.h"			//Isaac's math header
#include "GameState.h"		//Game states
#include "UIComponent.h"	//UI
