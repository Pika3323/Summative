#include "Engine.h"
#include "World.h"

#define GRID_SIZE 32

int main() {
	ALLEGRO_FONT *font = NULL;	//A font for debugging purposes
	ALLEGRO_DISPLAY *display;			//The display window
	ALLEGRO_EVENT_QUEUE *event_queue;	//The "event_queue"
	ALLEGRO_TIMER *timer;				//The loop timer
	ALLEGRO_BITMAP *dubBuff = NULL;
	int wWidth = 640, wHeight = 480;
	bool done = false;
	bool bOpenGL = true, bDirect3D = false;
	World CurrentWorld = World(Vector2D(8192, 4092), GRID_SIZE);
	Vector2D Clicked;
	GridTile clickedTile;
	bool bClicked = false;
	bool bRedraw = false;

	//Load Allegro and all required modules
	if (!al_init()) {
		fprintf(stderr, "Allegro could not initialize\n");
		return -1;
	}
	else {
		printf("Loaded Allegro %s\n", ALLEGRO_VERSION_STR);
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Allegro Primitives Addon could not initialize\n");
		return -1;
	}
	else {
		printf("Loaded Allegro Primitives Addon %s\n", ALLEGRO_VERSION_STR);
	}
	if (!al_install_keyboard()) {
		fprintf(stderr, "Keyboard drivers could not be installed\n");
		return -1;
	}
	else{
		printf("Keyboard drivers installed\n");
	}
	if (!al_install_mouse()){
		fprintf(stderr, "Mouse drivers could not be installed\n");
		return -1;
	}
	else{
		printf("Mouse drivers installed\n");
	}

	//FOR DEBUG
	al_init_font_addon();

	//Creates a builtin font that can be used on any computer without require ttf font files everywhere
	font = al_create_builtin_font();
	if (!font) {
		fprintf(stderr, "Could load font\n");
		return -1;
	}
	else {
		printf("Loaded font\n");
	}

	//create event loop stuff
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);	//Run the program at 60FPS
	dubBuff = al_create_bitmap(640, 480);

	if (bOpenGL){
		al_set_new_display_flags(ALLEGRO_OPENGL);
	}
	else if (bDirect3D){
		al_set_new_display_flags(ALLEGRO_DIRECT3D);
	}
	
	//Create the main display window
	display = al_create_display(wWidth, wHeight);

	//Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_set_target_bitmap(dubBuff);
	int sum = 0;
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 15; j++){
			al_draw_line(i * CurrentWorld.gridSize, (j + 1) * CurrentWorld.gridSize, (i + 1) * CurrentWorld.gridSize, (j + 1) * CurrentWorld.gridSize, al_map_rgb(255, 0, 0), 1);
			al_draw_line((i + 1) * CurrentWorld.gridSize, j * CurrentWorld.gridSize, (i + 1) * CurrentWorld.gridSize, (j + 1) * CurrentWorld.gridSize, al_map_rgb(255, 0, 0), 1);
			al_draw_textf(font, al_map_rgb(255, 0, 0), i * CurrentWorld.gridSize, j * CurrentWorld.gridSize, 0, "%d", sum);
			sum++;
		}
	}
	al_set_target_bitmap(al_get_backbuffer(display));


	al_flip_display();

	//Starts the timer which runs the following while loop at a certain rate (60FPS)	
	al_start_timer(timer);

	double old_time = al_get_time();

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);


		if (ev.type == ALLEGRO_EVENT_TIMER){
			bRedraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		//On KeyDown
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			default:
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			bClicked = true;
			Clicked = Vector2D(state.x, state.y);
			clickedTile = CurrentWorld.getClickedTile(Clicked);
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			bClicked = false;
		}

		//Close the window if the window's close button is closed, OR if the escape hey is pressed
		
		if(bRedraw && al_event_queue_is_empty(event_queue)){
			al_draw_bitmap(dubBuff, 0, 0, 0);

			if (bClicked) {
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 96, 0, "%d", clickedTile.id);
			}

			

			al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 112, 0, "x : %d", state.x);
			al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 128, 0, "y : %d", state.y);

			//Draws the framerate of the program on the screen
			double new_time = al_get_time();
			double delta = new_time - old_time;
			double fps = 1 / (delta);	bClicked = true;

			old_time = new_time;
			ALLEGRO_COLOR tColor;

			if (fps > 30) {
				tColor = al_map_rgb(0, 255, 0);
			}
			else {
				tColor = al_map_rgb(255, 0, 0);
			}

			al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 17, 0, "%.2f FPS", fps);
			al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 33, 0, "%.2fMS", delta * 1000);
			al_draw_textf(font, tColor, al_get_display_width(display) - 75, 16, 0, "%.2f FPS", fps);
			al_draw_textf(font, tColor, al_get_display_width(display) - 75, 32, 0, "%.2fMS", delta * 1000);

			//Flips the buffer to the screen
			al_flip_display();

			//Clears the screen so that no strange overwriting occurs
			al_clear_to_color(al_map_rgb(0, 0, 0));
			bRedraw = false;
		}
	}

	//Destroy everything after the loop is exited
	al_destroy_bitmap(dubBuff);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();

	return 0;
}

