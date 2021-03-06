//Standard Engine header
//Contains all the necessary headers for anything using the Engine

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

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0, 0);

//The core headers of the Engine
#include "Core.h"

//An encapsulation for debug outputs
struct DebugOutput{
	//String to output
	char output[256];

	//Color of the output
	ALLEGRO_COLOR color;

	//Maximum duration of the output
	float duration;

	//Time that the output has been on the screen
	float elapsedTime;

	DebugOutput(ALLEGRO_COLOR c, const char* text, float d){
		color = c;
		strcpy(output, text);
		duration = d;
		elapsedTime = 0;
	}
};

class Engine{
public:
	//The version of the engine that is being run
	int VersionMajor = 1;
	int VersionMinor = 2;

	//Get a reference to the current display
	ALLEGRO_DISPLAY* GetDisplay();

	//Get the current display data
	ALLEGRO_DISPLAY_MODE GetDisplayData();

	//Get a reference to the current game timer
	ALLEGRO_TIMER* GetTimer();

	//Get the debug font
	ALLEGRO_FONT* GetDebugFont();

	//Get a reference to the current event queue
	ALLEGRO_EVENT_QUEUE* GetEventQueue();

	//Get the mouse's current state
	ALLEGRO_MOUSE_STATE GetMouseState();

	//Get the keyboard's current state
	ALLEGRO_KEYBOARD_STATE GetKeyboardState();

	//Get a reference to the active GameState
	class GameState* GetCurrentGameState();

	//Get the current displays width
	int GetDisplayWidth();

	//Get the current displays height
	int GetDisplayHeight();

	//Lock all input functions to a specific UI component (for things such as text boxes)
	void LockInputToUIComponent(class UIComponent *c);

	//Whether input is currently locked to a UI component
	bool IsInputLocked();

	//Release input from all UI Components
	void ReleaseInput();

	//Draws the program's current frame rate
	void DrawFPS(double detla);

	//Prints debug text to the screen for a set duration of time
	//Be careful of using these in Tick functions!!
	void PrintDebugText(ALLEGRO_COLOR c, float duration, const char* text);

	//Prints debug text to the screen from an ALLEGRO_USTR*
	void PrintDebugText(ALLEGRO_COLOR c, float duration, ALLEGRO_USTR* text);
	
	//Initialize all engine components
	void Init();

	//Cleanup memory when game is exited
	void Cleanup();

	//Change game states
	template <class T> void ChangeGameState(){
		//Destroys the active gamestate if one exists
		if (Active){
			Active->Destroy();
			delete Active;
		}
		
		//Creates the new gamestate
		Active = new T();
		Active->Init();
	}

	//Handles all input
	void HandleInput(ALLEGRO_EVENT *ev);
	
	//Called every frame
	void Tick(float delta);

	//Draws everything to the screen
	void Draw();

	//Quits the game
	static void Quit();

	//Whether the game should continue to run its main loop, or exit
	bool ShouldTick();

	//Whether the screen should be redrawn
	bool ShouldRedraw();
	
	//The time between two frames
	double delta;

	//Determines whether to exit the program
	static bool bExit;

	//Structure containing cross-gamestate information
	Share SharedVar;

	Engine();
	
private:
	//Framerate at which the game runs
	const int FPS = 60;

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

	//Component in which input is locked to
	UIComponent* LockedComponent;
	
	//Whether to redraw the screen
	bool bRedraw;

	//Active game state
	class GameState* Active;

	//Initial height and width of the screen
	int DisplayHeight = 720, DisplayWidth = 1280;

	//Vector of all existing debug outputs
	std::vector<DebugOutput> DebugStrings;
};

//Declare the global engine instance
extern Engine* GEngine;