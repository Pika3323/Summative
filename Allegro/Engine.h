//Standard Engine header
//Contains all the nescessary headers for anything using the Engine

#pragma once

#define MOUSE_LB 1
#define MOUSE_RB 2
#define MOUSE_MB 3

//Material Colors (Blue in this case)
#define BLUE50	al_map_rgb(227, 242, 253)
#define BLUE100	al_map_rgb(187, 222, 251)
#define BLUE200	al_map_rgb(144, 202, 249)
#define BLUE300	al_map_rgb(100, 181, 246)
#define BLUE400	al_map_rgb(66, 165, 245)
#define BLUE500 al_map_rgb(33, 150, 243)
#define BLUE600	al_map_rgb(30, 136, 229)
#define BLUE700 al_map_rgb(25, 118, 210)
#define BLUE800 al_map_rgb(21, 101, 192)
#define BLUE900 al_map_rgb(13, 71, 161)

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
	ALLEGRO_KEYBOARD_STATE GetKeyboardState();
	int GetDisplayWidth();
	int GetDisplayHeight();

	void LockInputToUIComponent(class UIComponent *c);
	void ReleaseInput();

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
	void Tick(float delta);
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
	ALLEGRO_KEYBOARD_STATE keyboard_state;
	ALLEGRO_BITMAP* master_buffer;

	UIComponent* LockedComponent;
	
	bool bRedraw;
	int StateIndex;
	class GameState* Active;
	int DisplayHeight = 720, DisplayWidth = 1280;
};

bool Engine::bExit = false;


Engine* GEngine = new Engine();
#endif