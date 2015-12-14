#include "Engine.h"
#include "World.h"
#include "Buffer.h"
#include "UI.h"


#define GRID_SIZE 32
const int FPS = 60;

int main(int argc, char* argv[]) {
	CURL *curl;
	CURLcode res;
	bool bFullscreen = false, nRand = false;
	ALLEGRO_FONT *font = NULL;	//A font for debugging purposes
	ALLEGRO_DISPLAY *display;			//The display window
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue;	//The "event_queue"
	ALLEGRO_TIMER *timer;				//The loop timer
	ALLEGRO_BITMAP *backgroundImg;		//a temporary bitmap to hold the background photo
	Character TinTin = Character(Vector2D(0, 0), 64, 128);	//TinTin character
	Gravity CurrentGrav = Gravity(Vector2D(0.f, 5.f));		//current world gravity
	Buffer notPlayingBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f)); //block buffer for when not playing
	Buffer blockBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//play buffer for blocks
	Buffer dubBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//buffer for grid
	Buffer Background = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(2.5f, 2.5f));	//buffer for background
	int wWidth = 1280, wHeight = 720;	//Width and height of the window
	bool done = false;					//Whether the main loop is "done" (aka terminated)
	bool bOpenGL = true;		//Whether to use OpenGL
	World* CurrentWorld = new World(Vector2D(4096.f, 2048.f), GRID_SIZE);	//Creates the current world as well as a grid to store all the blocks
	Vector2D Clicked;	//The location of a click
	GridTile clickedTile;	//The clicked tile from the world grid
	bool bClicked = false;	//Whether a click was registered
	bool bRedraw = false;	//Whether to redraw the screen
	EBlockType SelectedBlock = EBlockType::B_Brick;		//the block type the user selects
	bool bDrawFPS = true, bDrawMouseLoc = false, bDrawClickID = false;
	Vector2D moveDelta = Vector2D(0.f, 0.f);
	CurrentWorld->bPlay = false;	//play functions are auto set off
	bool TinTinGrav = true;
	TinTin.gravSlot = CurrentGrav.Register(&TinTin, TinTinGrav);	//registering main character in gravity queue (is affected at beginning)
	bool DeleteMode = false;

	bool bBoxSelect = false;
	GridTile FirstTile;

	//keyboard bool catches
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	//Mouse Drag
	bool bMouseDrag = false;
	Vector2D DragStart;
	float DragTime = 0.f;
	double delta;
	Vector2D DragVelocity = Vector2D(-1.f, -1.f);

	for (int i = 1; i < argc; i++){
		if (strcmp(argv[i], "-nrand") == 0){
			nRand = true;
		}
		else if (strcmp(argv[i], "-f") == 0){
			bFullscreen = true;
		}
	}

	if (!nRand){
		srand(time(0));
	}

	//cUrl stuff
	/*curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (!curl){
		fprintf(stderr, "Could not create cUrl handle\n");
		return -1;
	}
	else{
		printf("Loaded cUrl %s\n", curl_version);
		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/test.php");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "testValue=YourFace");

		res = curl_easy_perform(curl);

		if (res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		}
		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();
	*/
	
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
	al_init_ttf_addon();
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
	backgroundImg = al_load_bitmap("Textures/Background_Original.png");
	notPlayingBuff.image = al_create_bitmap(4096, 2048);
	Background.image = al_create_bitmap(4096, 2048);
	blockBuff.image = al_create_bitmap(4096, 2048);


	//Set ALLEGRO_DISPLAY flags
	if (bOpenGL){
		al_set_new_display_flags(ALLEGRO_OPENGL);
	}

	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);

	//Create the main display window
	if (bFullscreen){
		al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		display = al_create_display(disp_data.width, disp_data.height);
	}
	else{
		display = al_create_display(wWidth, wHeight);
	}
	

	//MainMenu(display, wWidth, wHeight);

	//Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	CurrentWorld->Type[0] = BlockType("Rainbow", al_load_bitmap("Textures/Rainbow.png"));
	CurrentWorld->Type[1] = BlockType("Brick", al_load_bitmap("Textures/Brick.png"));
	CurrentWorld->Type[2] = BlockType("Grass", al_load_bitmap("Textures/Grass.png"));
	CurrentWorld->Type[3] = BlockType("Dirt", al_load_bitmap("Textures/Dirt.png"));
	CurrentWorld->Type[4] = BlockType("Stone", al_load_bitmap("Textures/Stone.png"));
	CurrentWorld->Type[5] = BlockType("Fancy", al_load_bitmap("Textures/Fancy.png"));
	CurrentWorld->Type[6] = BlockType("Mossy", al_load_bitmap("Textures/Mossy.png"));

	//Clear screen to black
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	//Setting Multiple Images to Background Buffer
	al_set_target_bitmap(Background.image);

	for (int i = 0; i < 2; i++) {
		for (int y = 0; y < 3; y++) {
			al_draw_bitmap(backgroundImg, (y * 1024), (i * 1024), 0);
		}
	}

	al_set_target_bitmap(al_get_backbuffer(display));
	//Sets the draw target to the grid bitmap

	al_set_target_bitmap(dubBuff.image);

	for (int i = 0; i < 129; i++){
		al_draw_line(i * GRID_SIZE, 0, i * GRID_SIZE, 2048, al_map_rgba(50, 50, 50, 150), 1);
	}
	for (int i = 0; i < 65; i++){
		al_draw_line(0, i * GRID_SIZE, 4096, i * GRID_SIZE, al_map_rgba(50, 50, 50, 150), 1);
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
		if (CurrentWorld->Load(loadLevel)){
			printf("Loaded %s\n", loadLevel);
		}
		else{
			printf("Could not load %s\n", loadLevel);
		}
	}

	//Starts the timer which runs the following while loop at a certain rate (60FPS)	
	al_start_timer(timer);

	//Gets a starting time in order to calculate a delta time
	double old_time = al_get_time();

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
		//On KeyDown event
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				//Close window if escape key is pressed
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					TinTin.flipped = false;
					moveDelta.x = -5.f;
					TinTin.moving = true;
					break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					moveDelta.x = 5.f;
					TinTin.moving = true;
					TinTin.flipped = true;
					break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					moveDelta.y = -5.f;
					break;
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					moveDelta.y = 5.f;
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
				case ALLEGRO_KEY_C:
					bBoxSelect = !bBoxSelect;
					break;
				case ALLEGRO_KEY_1:
					SelectedBlock = EBlockType::B_Rainbow;
					break;
				case ALLEGRO_KEY_2:
					SelectedBlock = EBlockType::B_Brick;
					break;
				case ALLEGRO_KEY_3:
					SelectedBlock = EBlockType::B_Grass;
					break;
				case ALLEGRO_KEY_4:
					SelectedBlock = EBlockType::B_Dirt;
					break;
				case ALLEGRO_KEY_5:
					SelectedBlock = EBlockType::B_Stone;
					break;
				case ALLEGRO_KEY_6:
					SelectedBlock = EBlockType::B_Fancy;
					break;
				case ALLEGRO_KEY_7:
					SelectedBlock = EBlockType::B_Mossy;
					break;
				case ALLEGRO_KEY_SPACE:
					if (!CurrentWorld->bPlay){
						CurrentWorld->bPlay = true;
					}
					else {
						CurrentWorld->bPlay = false;
						TinTin.position = Vector2D(0.f, 0.f);
					}
					CurrentGrav.GonOff[TinTin.gravSlot] = true;
				case ALLEGRO_KEY_BACKSPACE:
					if (!DeleteMode) {
						DeleteMode = true;
					}
					else {
						DeleteMode = false;
					}

				default:
					break;
			}
		}
		//On KeyUp
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				TinTin.moving = false;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				moveDelta.x = 0.f;
				TinTin.moving = false;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				moveDelta.y = 0.f;
				break;
			default:
				break;
			}
		}

		//On mouse click
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			switch (ev.mouse.button){
			case MOUSE_LB:
				if (!CurrentWorld->bPlay) {
					bClicked = true;
					if (!bBoxSelect) {
						//Get the mouse's location
						Clicked = Vector2D(state.x + (dubBuff.offset.x * -1), state.y + (dubBuff.offset.y * -1));
						//Get the tile that was clicked
						clickedTile = CurrentWorld->getClickedTile(Clicked);

						if (!DeleteMode) {
							//if the tile is not already occupied by a block, create a new block
							if (!clickedTile.occupied){
								CurrentWorld->Blocks[clickedTile.x][clickedTile.y] = Block(clickedTile.location, SelectedBlock);
								CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = true;
								clickedTile.occupied = true;
							}
						}
						else if (DeleteMode) {
							CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = false;
							clickedTile.occupied = false;
						}

					}
					else{
						Clicked = Vector2D(state.x + (dubBuff.offset.x * -1), state.y + (dubBuff.offset.y * -1));

						FirstTile = CurrentWorld->getClickedTile(Clicked);
					}
				}
				break;
			case MOUSE_RB:
				bMouseDrag = true;
				DragStart = Vector2D(ev.mouse.x, ev.mouse.y);
				break;
			case MOUSE_MB:
				printf("mmb pressed\n");
				break;
			}
		}
		//On MouseUp
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			bClicked = false;

			if (ev.mouse.button == MOUSE_RB){
				bMouseDrag = false;
				DragVelocity = DragStart / DragTime;
			}
		}
		//Tick
		if (ev.type == ALLEGRO_EVENT_TIMER){
			if (CurrentWorld->Blocks[(int)(TinTin.position.x / GRID_SIZE)][(int)(TinTin.position.y + TinTin.ActualHeight) / GRID_SIZE].bSpawned) {
				CurrentGrav.GonOff[TinTin.gravSlot] = false;
				al_destroy_bitmap(TinTin.spritesheet);
				TinTin.DoEv('i');
			}
			else if (!CurrentWorld->Blocks[(int)(TinTin.position.x / GRID_SIZE)][(int)(TinTin.position.y + TinTin.ActualHeight) / GRID_SIZE].bSpawned) {
				CurrentGrav.GonOff[TinTin.gravSlot] = true;
			}
			if (CurrentGrav.GonOff[TinTin.gravSlot]) {
				al_destroy_bitmap(TinTin.spritesheet);
				TinTin.DoEv('f');
			}
			if (TinTin.moving && TinTin.animation == 'f') {
				if (!TinTin.flipped)
					TinTin.position.x += TinTin.delta.x;
				else
					TinTin.position.x -= TinTin.delta.x;
			}
			else if (TinTin.moving) {
				al_destroy_bitmap(TinTin.spritesheet);
				TinTin.DoEv('r');
				if (!TinTin.flipped)
					TinTin.position.x += TinTin.delta.x;
				else
					TinTin.position.x -= TinTin.delta.x;
			}
			if (CurrentWorld->bPlay) {
				CurrentGrav.Tick();
			}
			TinTin.EvHandle();
			CurrentWorld->Tick(delta);
			bRedraw = true;
			CurrentWorld->moveWorld(moveDelta, dubBuff, Background, blockBuff, notPlayingBuff, wWidth, wHeight);
			if (bMouseDrag){
				Vector2D DragDelta = DragStart - Vector2D(state.x, state.y);
				CurrentWorld->moveWorld(DragDelta * -1, dubBuff, Background, blockBuff, notPlayingBuff, wWidth, wHeight);
				DragStart = Vector2D(state.x, state.y);
				DragTime += delta;
			}
			if (bClicked && !bBoxSelect){
				Clicked = Vector2D(state.x + (dubBuff.offset.x * -1), state.y + (dubBuff.offset.y * -1));

				//Get the tile that was clicked
				clickedTile = CurrentWorld->getClickedTile(Clicked);
				if (!DeleteMode) {
					//if the tile is not already occupied by a block, create a new block
					if (!clickedTile.occupied){
						CurrentWorld->Blocks[clickedTile.x][clickedTile.y] = Block(clickedTile.location, SelectedBlock);
						CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = true;
						clickedTile.occupied = true;
					}
				}
				else if (DeleteMode) {
					CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = false;
					clickedTile.occupied = false;
				}
			}

		}
		//Redraw the screen 
		//DO NOT PUT TICK CODE HERE!!!
		if (bRedraw && al_event_queue_is_empty(event_queue)){
			//Draws the framerate of the program on the screen
			double new_time = al_get_time();
			delta = new_time - old_time;
			old_time = new_time;

			if (!CurrentWorld->bPlay){
				al_set_target_bitmap(notPlayingBuff.image);
				al_clear_to_color(al_map_rgba(0, 0, 0, 0));
			}
			else{
				al_set_target_bitmap(blockBuff.image);
				al_clear_to_color(al_map_rgba(0, 0, 0, 0));
				TinTin.Animate(TinTin.flipped);
			}
			//Foreach loop that goes through every block
			
			al_hold_bitmap_drawing(true);
			for (auto& sub : CurrentWorld->Blocks){
				for (auto& elem : sub){
					//If the block has been created, draw it!
					elem.offset = elem.position + CurrentWorld->offset;

					if (elem.bSpawned && InRange(elem.offset.x, -32, wWidth + 32) && InRange(elem.offset.y, -32, wHeight + 32)){
						elem.Draw(CurrentWorld->Type[static_cast<int>(elem.type)].texture);
					}
				}	
			}

			al_hold_bitmap_drawing(false);

			if (bBoxSelect) {
				GridTile newTile = CurrentWorld->getClickedTile(Vector2D(state.x + (dubBuff.offset.x * -1), state.y + (dubBuff.offset.y * -1)));
				al_draw_filled_rectangle(FirstTile.location.x, FirstTile.location.y, newTile.location.x, newTile.location.y, al_map_rgba(137, 231, 255, 100));
			}

			//Draws TinTin character (idle, east)
			al_set_target_bitmap(al_get_backbuffer(display));

			al_draw_bitmap_region(Background.image, Background.offset.x * -1, Background.offset.y * -1, wWidth, wHeight, 0, 0, 0);


			if (!CurrentWorld->bPlay) {
				al_draw_bitmap_region(dubBuff.image, dubBuff.offset.x * -1, dubBuff.offset.y * -1, wWidth, wHeight, 0, 0, 0);
				al_draw_bitmap_region(notPlayingBuff.image, notPlayingBuff.offset.x * -1, notPlayingBuff.offset.y * -1, wWidth, wHeight, 0, 0, 0);
			}
			else {
				al_draw_bitmap_region(blockBuff.image, blockBuff.offset.x *-1, blockBuff.offset.y * -1, wWidth, wHeight, 0, 0, 0);
			}

			al_set_target_bitmap(al_get_backbuffer(display));

			//Draw mouse position
			if (bDrawMouseLoc){
				al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 113, 0, "x : %d", state.x);
				al_draw_textf(font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 74, 129, 0, "y : %d", state.y);
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 112, 0, "x : %d", state.x);
				al_draw_textf(font, al_map_rgb(255, 255, 255), al_get_display_width(display) - 75, 128, 0, "y : %d", state.y);
			}

			//Draw FPS
			if (bDrawFPS){
				DrawFPS(display, font, delta); 
			}
			al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 10, 0, "x : %d", Background.offset.x);
			al_draw_textf(font, al_map_rgb(0, 0, 0), 10, 26, 0, "y : %d", Background.offset.y);

			//Flips the buffer to the screen
			//h->draw();

			al_wait_for_vsync();

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

		if(CurrentWorld->Save(levelName)){

			printf("Saved level as %s\n", levelName);
		}
		else{
			printf("Could not save level as %s\n", levelName);
		}
	}

	//Destroy everything after the loop is exited
	al_destroy_bitmap(dubBuff.image);
	al_destroy_bitmap(TinTin.spritesheet);
	al_destroy_bitmap(blockBuff.image);
	al_destroy_bitmap(Background.image);
	al_destroy_bitmap(backgroundImg);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();

	delete CurrentWorld;

	return 0;
}
