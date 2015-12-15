//Standard Engine header
//Contains all the nescessary headers for anything using the Engine

#pragma once

#define MOUSE_LB 1
#define MOUSE_RB 2
#define MOUSE_MB 3

#include "Core.h"


class Engine{
public:
	const int FPS = 60;

	ALLEGRO_DISPLAY* GetDisplay();
	ALLEGRO_DISPLAY_MODE GetDisplayData();
	ALLEGRO_TIMER* GetTimer();
	ALLEGRO_FONT* GetDebugFont();
	ALLEGRO_EVENT_QUEUE* GetEventQueue();

	void DrawFPS(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, double detla);
	
	void Init();
	void Cleanup();

	void ChangeGameState(class GameState* state);
	void RegisterState(GameState* state);

	void HandleInput(ALLEGRO_EVENT *ev);
	void Tick();
	void Draw();

	void Quit();

	bool ShouldTick();
	bool ShouldRedraw();

	GameState* States[3];

	
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT* debug_font;
	bool bExit;
	bool bRedraw;
	int StateIndex;
};

#ifndef _ENGINE
#define _ENGINE
Engine* GEngine = new Engine();
#endif