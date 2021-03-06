#include "Engine.h"

/*
This Game was created and developped by Derek Ellis and Isaac Jensen-Large as a summative project for ICS3U at Lisgar Collegiate Institute in the 2015-2016 year
Development commenced: 
*/

Engine* GEngine = new Engine();

int main(int argc, char* argv[]){
	//Initialize the game engine
	GEngine->Init();

	//Get a time before loop starts to calculate the delta time of a frame/loop
	double old_time = al_get_time();

	//Only run the loop while the engine should keep ticking, otherwise quit
	while (GEngine->ShouldTick()) {
		//Events for the frame
		ALLEGRO_EVENT ev;
		//Wait for an event (an input, or timer event)
		al_wait_for_event(GEngine->GetEventQueue(), &ev);

		//If the close button was clicked, quit the program
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			GEngine->Quit();
			break;
		}
		//Run the functions for a single tick
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			GEngine->Tick(GEngine->delta);
		}
		//Handle all other inputs
		else {
			GEngine->HandleInput(&ev);
		}
		//Draw to the screen
		if (GEngine->ShouldRedraw() && al_event_queue_is_empty(GEngine->GetEventQueue())){
			//Calculate the change in time between two frames
			double new_time = al_get_time();
			GEngine->delta = new_time - old_time;
			old_time = new_time;

			//Draws everything from the current frame to the screen
			GEngine->Draw();
		}
	}
	//Cleanup
	GEngine->Cleanup();
	return 0;
}