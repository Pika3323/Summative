//Standard Engine header
//Contains all the nescessary headers for anything using the Engine

#pragma once

//Mouse buttons (since Allegro doesn't provide these)
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

//The core headers of the Engine
#include "Core.h"

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
	class GameState* GetCurrentGameState();
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

	void HandleInput(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	bool GamePaused();
	void PauseGame();

	static void Quit();

	bool ShouldTick();
	bool ShouldRedraw();

	class GameState* States[2];
	int ActiveState = 0;
	double delta;
	static bool bExit;

	Engine(){}
	
private:
	//The active game display
	ALLEGRO_DISPLAY *display;

	//Information about the active game display
	ALLEGRO_DISPLAY_MODE disp_data;

	//The current queue of events
	ALLEGRO_EVENT_QUEUE *event_queue;

	//The master timer
	ALLEGRO_TIMER *timer;
	
	//A font for debugging purposes
	ALLEGRO_FONT* debug_font;

	//The mouse's current state
	ALLEGRO_MOUSE_STATE mouse_state;

	//The keyboard's current state
	ALLEGRO_KEYBOARD_STATE keyboard_state;

	//The master output buffer
	ALLEGRO_BITMAP* master_buffer;

	UIComponent* LockedComponent;
	
	bool bRedraw;
	bool bGamePaused;
	int StateIndex;
	class GameState* Active;
	int DisplayHeight = 720, DisplayWidth = 1280;
};

//Static variable initialization
bool Engine::bExit = false;


Engine* GEngine = new Engine();