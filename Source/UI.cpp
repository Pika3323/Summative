#include "UI.h"

void MainMenu(ALLEGRO_DISPLAY* d, int w, int h){
	bool done = false, bRedraw = true;
	Buffer Background[2] = { Buffer(al_create_bitmap(w, h), Vector2D(0.f, 0.f), Vector2D(-5.f, 0.f)), Buffer(al_create_bitmap(w, h), Vector2D(w, 0.f), Vector2D(-5.f, 0.f)) };
	Button* BEditor = new Button(al_map_rgb(255, 255, 255), al_map_rgb(33, 150, 243), 100, 36, Vector2D(w/2, 0), 0, "EDITOR", NULL);
	Button* BLevels = new Button(al_map_rgb(255, 255, 255), al_map_rgb(33, 150, 243), 100, 36, Vector2D(w / 2, 48), 0, "LEVELS", NULL);
	Button* menuButtons[2] = { BEditor, BLevels };
	ALLEGRO_EVENT_QUEUE *event_queue;	//The "event_queue"
	ALLEGRO_TIMER *timer;				//The loop timer

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0f / 60.f);	//Run the program at 60FPS

	al_register_event_source(event_queue, al_get_display_event_source(d));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//Starts the timer which runs the following while loop at a certain rate (60FPS)	
	al_start_timer(timer);

	//Gets a starting time in order to calculate a delta time
	double old_time = al_get_time();

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//Gets current state of the mouse
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);

		//End the loop if the window's close button is clicked
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		}

		if (ev.type == ALLEGRO_EVENT_TIMER){
			bRedraw = true;
			for (auto& b : menuButtons){
				if (InRange(state.x, b->position.x, b->position.x + b->width) && InRange(state.y, b->position.y, b->position.y + b->height)){
					b->onHoverIn();
				}
				else {
					b->onHoverOut();
				}
			}
		}

		if (bRedraw && al_event_queue_is_empty(event_queue)){
			double new_time = al_get_time();
			double delta = new_time - old_time;
			old_time = new_time;

			for (auto& b : menuButtons){
				b->Draw();
			}

			al_wait_for_vsync();

			al_flip_display();

			//Clears the screen so that no strange overwriting occurs
			al_clear_to_color(al_map_rgb(0, 0, 0));
			bRedraw = false;
		}
	}
}