#include "Engine.h"
#include "World.h"
#include "Buffer.h"

#define GRID_SIZE 32
const int FPS = 60;
const char myLevel[20] = "testLevel.bvl";

int main() {
	ALLEGRO_FONT *font = NULL;	//A font for debugging purposes
	ALLEGRO_DISPLAY *display;			//The display window
	ALLEGRO_EVENT_QUEUE *event_queue;	//The "event_queue"
	ALLEGRO_TIMER *timer;				//The loop timer
	Buffer dubBuff = { NULL, 0.f, 0.f, 5.f, 5.f, false, false };
	ALLEGRO_BITMAP *blockTex = NULL;	//The test texture for block
	int wWidth = 640, wHeight = 480;	//Width and height of the window
	bool done = false;					//Whether the main loop is "done" (aka terminated)
	bool bOpenGL = true, bDirect3D = false;		//Whether to use OpenGL or Direct3D
	World* CurrentWorld = new World(Vector2D(8192.f, 4092.f), GRID_SIZE);	//Creates the current world as well as a grid to store all the blocks
	Vector2D Clicked;	//The location of a click
	GridTile clickedTile;	//The clicked tile from the world grid
	bool bClicked = false;	//Whether a click was registered
	bool bRedraw = false;	//Whether to redraw the screen
	FILE *fptr;
	Block blocks[8192];	//Array of all block in the world
	BlockType Type[15];
	bool bDrawFPS = true, bDrawMouseLoc = false, bDrawClickID = false;

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
	if (!al_init_image_addon()) {
		fprintf(stderr, "Allegro Image Addon could not initialize\n");
		return -1;
	}
	else {
		printf("Loaded Allegro Image Addon %s\n", ALLEGRO_VERSION_STR);
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
	//END LOADING OF ALL MODULES


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
	timer = al_create_timer(1.0f / FPS);	//Run the program at 60FPS
	dubBuff.image = al_create_bitmap(4096, 2048);
	

	//Set ALLEGRO_DISPLAY flags
	if (bOpenGL){
		al_set_new_display_flags(ALLEGRO_OPENGL);
	}
	else if (bDirect3D){
		al_set_new_display_flags(ALLEGRO_DIRECT3D);
	}
	
	
	//Create the main display window
	display = al_create_display(wWidth, wHeight);

	printf("%d\n", al_get_display_option(display, ALLEGRO_MAX_BITMAP_SIZE));

	

	//Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	blockTex = al_load_bitmap("Textures/TEST.png");

	Type[0] = BlockType("Rainbow", blockTex);


	//Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	//Sets the draw target to the grid bitmap
	al_set_target_bitmap(dubBuff.image);
	int sum = 0;
	
	//Draws a grid based on the tiles of the world
	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 64; j++){
			al_draw_line(i * CurrentWorld->gridSize, (j + 1) * CurrentWorld->gridSize, (i + 1) * CurrentWorld->gridSize, (j + 1) * CurrentWorld->gridSize, al_map_rgb(0, 255, 0), 1);
			al_draw_line((i + 1) * CurrentWorld->gridSize, j * CurrentWorld->gridSize, (i + 1) * CurrentWorld->gridSize, (j + 1) * CurrentWorld->gridSize, al_map_rgb(0, 255, 0), 1);
			al_draw_textf(font, al_map_rgb(0, 255, 0), i * CurrentWorld->gridSize, j * CurrentWorld->gridSize, 0, "%d", sum);
			sum++;
		}
	}
	//Sets the target bitmap back to the default buffer
	al_set_target_bitmap(al_get_backbuffer(display));
	
	//Draws everything to the screen
	al_flip_display();

	printf("Read saved level? (y/n): ");
	char cRead;
	scanf("%c", &cRead);
	if (tolower(cRead) == 'y'){
		fflush(stdin);
		char loadLevel[64];
		printf("Enter level name: ");
		scanf("%s", loadLevel);
		fflush(stdin);
		strcat(loadLevel, ".bvl");
		fptr = fopen(myLevel, "rb");

		for (int i = 0; i < 8192; i++){
			fseek(fptr, sizeof(Block)*i, SEEK_SET);
			fread(&blocks[i], sizeof(Block), 1, fptr);
		}
		fclose(fptr);
		fptr = NULL;
	}

	for (auto& elem : blocks){

	}

	//Starts the timer which runs the following while loop at a certain rate (60FPS)	
	al_start_timer(timer);

	//Gets a starting time in order to calculate a delta time
	double old_time = al_get_time();

	printf("%d\n", al_get_bitmap_flags(dubBuff.image));
	//Main tick loop
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
		//On KeyDown
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				//Close window if escape key is pressed
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					dubBuff.bdx = true;
					dubBuff.dx = -5;
					break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					dubBuff.bdx = true;
					dubBuff.dx = 5;
					break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					dubBuff.bdy = true;
					dubBuff.dy = -5;
					break;
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					dubBuff.bdy = true;
					dubBuff.dy = 5;
					break;
				case ALLEGRO_KEY_I:
					bDrawFPS = !bDrawFPS;
					break;
				case ALLEGRO_KEY_O:
					bDrawClickID = !bDrawClickID;
					break;
				case ALLEGRO_KEY_P:
					bDrawMouseLoc = !bDrawMouseLoc;
					break;
				default:
					break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_RIGHT:
				dubBuff.bdx = false;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_DOWN:
				dubBuff.bdy = false;
				break;
			default:
				break;
			}
		}

		//On mouse click
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			bClicked = true;

			//Get the mouse's location
			Clicked = Vector2D(state.x + (dubBuff.x * -1), state.y + (dubBuff.y * -1));

			//Get the tile that was clicked
			clickedTile = CurrentWorld->getClickedTile(Clicked);

			//if the tile is not already occupied by a block, create a new block
			if (!clickedTile.occupied){
				blocks[clickedTile.id] = Block(clickedTile.location, EBlockType::B_Rainbow);
				blocks[clickedTile.id].bSpawned = true;
				clickedTile.occupied = true;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			bClicked = false;
		}

		//Tick
		if (ev.type == ALLEGRO_EVENT_TIMER){
			bRedraw = true;
			if (dubBuff.bdx) {
				dubBuff.x += dubBuff.dx;
				CurrentWorld->offset.x += dubBuff.dx;
			}
			if (dubBuff.bdy) {
				dubBuff.y += dubBuff.dy;
				CurrentWorld->offset.y += dubBuff.dy;
			}
			CurrentWorld->Tick();
		}
		
		
		//Redraw the screen 
		//DO NOT PUT TICK CODE HERE!!!
		if(bRedraw && al_event_queue_is_empty(event_queue)){
			al_hold_bitmap_drawing(true);
			//Draws the framerate of the program on the screen
			double new_time = al_get_time();
			double delta = new_time - old_time;
			double fps = 1 / (delta);
			old_time = new_time;
			ALLEGRO_COLOR tColor;

			if (fps > 30) {
				tColor = al_map_rgb(0, 255, 0);
			}
			else {
				tColor = al_map_rgb(255, 0, 0);
			}

			al_set_target_bitmap(dubBuff.image);
			//Foreach loop that goes through every block
			
			for (auto& elem : blocks){
				//If the block has been created, draw it!
				if (elem.bSpawned){
					al_draw_bitmap(Type[static_cast<int>(elem.type)].texture, elem.position.x, elem.position.y, ALLEGRO_VIDEO_BITMAP);
					al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 112, 0, "%a", al_get_bitmap_flags(Type[static_cast<int>(elem.type)].texture));
				}
			}
			
			al_set_target_bitmap(al_get_backbuffer(display));

			al_draw_bitmap_region(dubBuff.image, dubBuff.x * -1, dubBuff.y * -1, wWidth, wHeight, 0, 0, 0);

			//al_draw_bitmap(dubBuff.image, dubBuff.x, dubBuff.y, 0);

			//Draw mouse position
			if (bDrawMouseLoc){
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 112, 0, "x : %d", state.x);
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 128, 0, "y : %d", state.y);
			}

			if (bClicked && bDrawClickID) {
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 96, 0, "%d", clickedTile.id);
			}
			
			//Draw FPS
			if (bDrawFPS){
				al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 17, 0, "%.2f FPS", fps);
				al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 33, 0, "%.2fMS", delta * 1000);
				al_draw_textf(font, tColor, al_get_display_width(display) - 75, 16, 0, "%.2f FPS", fps);
				al_draw_textf(font, tColor, al_get_display_width(display) - 75, 32, 0, "%.2fMS", delta * 1000);
			}
			al_hold_bitmap_drawing(false);
			//Flips the buffer to the screen
			al_flip_display();

			//Clears the screen so that no strange overwriting occurs
			al_clear_to_color(al_map_rgb(0, 0, 0));
			bRedraw = false;
		}
	}
	fflush(stdin);

	printf("Save level? (y/n): ");
	char cSave;
	scanf("%c", &cSave);
	fflush(stdin);
	if (tolower(cSave) == 'y'){
		char levelName[64];
		printf("Enter a file name: ");
		scanf("%s", levelName);
		strcat(levelName, ".bvl");

		fptr = fopen(myLevel, "wb+");

		for (auto& b : blocks){
			fwrite(&b, sizeof(Block), 1, fptr);
		}

		fclose(fptr);
	}

	//Destroy everything after the loop is exited
	al_destroy_bitmap(dubBuff.image);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();

	delete CurrentWorld;

	return 0;
}

