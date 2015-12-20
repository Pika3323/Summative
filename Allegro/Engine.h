//Standard Engine header
//Contains all the nescessary headers for anything using the Engine

#pragma once

#define MOUSE_LB 1
#define MOUSE_RB 2
#define MOUSE_MB 3

#include "Core.h"

#ifndef _ENGINE
#define _ENGINE

class Engine{
public:
	const int FPS = 60;

	ALLEGRO_DISPLAY* GetDisplay();
	ALLEGRO_DISPLAY_MODE GetDisplayData();
	ALLEGRO_TIMER* GetTimer();
	ALLEGRO_FONT* GetDebugFont();
	ALLEGRO_EVENT_QUEUE* GetEventQueue();
	ALLEGRO_MOUSE_STATE GetMouseState();
	int GetDisplayWidth();
	int GetDisplayHeight();

	void DrawFPS(double detla);
	
	void Init();
	void Cleanup();

	template <class T> void ChangeGameState(){
		if (Active){
			Active->Destroy();
			delete Active;
		}
		Active = new T();
		Active->Init();
	}
	//void RegisterState(class GameState* state);

	void HandleInput(ALLEGRO_EVENT *ev);
	void Tick();
	void Draw();

	static void Quit();

	bool ShouldTick();
	bool ShouldRedraw();

	class GameState* States[2];
	int ActiveState = 0;
	double delta;
	static bool bExit;

	Engine(){}
	
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT* debug_font;
	ALLEGRO_MOUSE_STATE mouse_state;
	ALLEGRO_BITMAP* master_buffer;
	
	bool bRedraw;
	int StateIndex;
	class GameState* Active;
	int DisplayHeight = 720, DisplayWidth = 1280;
};

bool Engine::bExit = false;


Engine* GEngine = new Engine();
#endif