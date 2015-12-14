//Standard Engine header
//Contains all the nescessary headers for anything using the Engine

#pragma once

#define MOUSE_LB 1
#define MOUSE_RB 2
#define MOUSE_MB 3

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_opengl.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "Vector2D.h"
#include "Block.h"
#include "Buffer.h"
#include "IMath.h"
#include "Character.h"
#include "Button.h"
#include "Buffer.h"
#include "Effects.h"
#include "Input.h"
#include "curl/curl.h"

void DrawFPS(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, double detla);



