#pragma once

//Allegro headers
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>

//libcurl headers
#include "curl/curl.h"

//Standard headers
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <vector>

//Core Engine components
#include "Vector2D.h"		//Vector header, including some vector math
#include "IMath.h"			//Isaac's math header
#include "GameState.h"		//Game states
#include "UIComponent.h"	//UI
