#include "Engine.h"

int main(int argc, char* argv[]){

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
		
		if (GEngine->ShouldRedraw() && al_event_queue_is_empty(GEngine->GetEventQueue())){
			GEngine->Draw();
		}
	}

	GEngine->Cleanup();

	return 0;
}