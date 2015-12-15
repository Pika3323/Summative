#include "Engine.h"

int main(int argc, char* argv[]){

	//Initialize the game engine
	GEngine->Init();

	while (GEngine->ShouldTick()) {

		if (!GEngine->States[0]->Initialized) {
			GEngine->States[0]->Init();
			GEngine->States[0]->Initialized = true;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(GEngine->GetEventQueue(), &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			GEngine->Quit();
			break;
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