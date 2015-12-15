#include "Engine.h"

int main(int argc, char* argv[]){

	//Initialize the game engine
	GEngine->Init();

	while (GEngine->ShouldTick()){
		ALLEGRO_EVENT ev;
		al_wait_for_event(GEngine->GetEventQueue(), &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			GEngine->Quit();
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			GEngine->Tick();
		}
		else{
			GEngine->HandleInput(&ev);
		}
		
		//Draw to the screen
		if (GEngine->ShouldRedraw() && al_event_queue_is_empty(GEngine->GetEventQueue())){
			GEngine->Draw();
		}
	}

	//Cleanup
	GEngine->Cleanup();

	return 0;
}