#include "Engine.h"

int main(int argc, char* argv[]){

	//Initialize the game engine
	GEngine->Init();

	double old_time = al_get_time();

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
		else {
			GEngine->HandleInput(&ev);
		}
		
		//Draw to the screen
		if (GEngine->ShouldRedraw() && al_event_queue_is_empty(GEngine->GetEventQueue())){
			double new_time = al_get_time();
			double delta = new_time - old_time;
			old_time = new_time;

			GEngine->Draw();
			al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
			GEngine->DrawFPS(delta);
		}
	}

	//Cleanup
	GEngine->Cleanup();

	return 0;
}