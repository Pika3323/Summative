#include "Engine.h"
#include "PlayState.h"
#include "MainMenuState.h"

//Static variable initialization
bool Engine::bExit = false;

Engine::Engine(){
	Active = NULL;
	LockedComponent = NULL;
}

ALLEGRO_DISPLAY* Engine::GetDisplay(){
	return display;
}

ALLEGRO_TIMER* Engine::GetTimer(){
	return timer;
}

ALLEGRO_DISPLAY_MODE Engine::GetDisplayData(){
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	return disp_data;
}

ALLEGRO_FONT* Engine::GetDebugFont(){
	return debug_font;
}

ALLEGRO_EVENT_QUEUE* Engine::GetEventQueue(){
	return event_queue;
}

ALLEGRO_MOUSE_STATE Engine::GetMouseState(){
	return mouse_state;
}

ALLEGRO_KEYBOARD_STATE Engine::GetKeyboardState(){
	return keyboard_state;
}

void Engine::DrawFPS(double delta){
	ALLEGRO_COLOR tColor;
	if (1 / delta >= 30){
		 tColor = al_map_rgb(0, 255, 0);
	}
	else{
		tColor = al_map_rgb(255, 0 , 0);
	}
	al_draw_textf(debug_font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 17, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
	al_draw_textf(debug_font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 33, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);

	al_draw_textf(debug_font, tColor, al_get_display_width(display) - 6, 16, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
	al_draw_textf(debug_font, tColor, al_get_display_width(display) - 6, 32, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);
}

void Engine::Init(){
	srand(time(0));

	//Version info
	printf("Summative version %d.%d\n", VersionMajor, VersionMinor);
	
	//Allegro
	if (!al_init()) {
		fprintf(stderr, "Allegro could not initialize\n");
		bExit = true;
	}
	else {
		printf("Loaded Allegro %s\n", ALLEGRO_VERSION_STR);
	}

	//Primitives
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Allegro Primitives Addon could not initialize\n");
		bExit = true;
	}
	else {
		printf("Loaded Allegro Primitives Addon %s\n", ALLEGRO_VERSION_STR);
	}

	//Image
	if (!al_init_image_addon()) {
		fprintf(stderr, "Allegro Image Addon could not initialize\n");
		bExit = true;
	}
	else {
		printf("Loaded Allegro Image Addon %s\n", ALLEGRO_VERSION_STR);
	}

	//Keyboard Drivers
	if (!al_install_keyboard()) {
		fprintf(stderr, "Keyboard drivers could not be installed\n");
		bExit = true;
	}
	else{
		printf("Keyboard drivers installed\n");
	}

	//Mouse Drivers
	if (!al_install_mouse()){
		fprintf(stderr, "Mouse drivers could not be installed\n");
		bExit = true;
	}
	else{
		printf("Mouse drivers installed\n");
	}

	//Font add on
	if (!al_init_font_addon() || !al_init_ttf_addon()){
		fprintf(stderr, "Font add on could not be loaded\n");
		bExit = true;
	}
	else{
		printf("Font add on loaded\n");
	}

	//Create a font for the use of debugging
	//debug_font = al_create_builtin_font();
	debug_font = al_load_ttf_font("Roboto-Regular.ttf", 11, 0);
	if (!debug_font) {
		fprintf(stderr, "Debugging font could not be created\n");
		bExit = true;
	}

	//Create the event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "Event queue could not be created\n");
	}

	timer = al_create_timer(1.0f / FPS);	//Run the game at 60FPS

	//Using the OpenGL flag for a bit of hardware acceleration
	al_set_new_display_flags(ALLEGRO_OPENGL);

	//Set the window's title
	//Yes, the extra "e" is supposed to be there
	al_set_new_window_title("The Block Gamee");

	//Create the main display
	display = al_create_display(1280, 720);

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//Register all of the required event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//master_buffer = al_create_bitmap(DisplayWidth, DisplayHeight);

	//Start the game timer
	al_start_timer(timer);

	//Change the current game state to the main menu state
	ChangeGameState<MainMenuState>();
}

void Engine::Cleanup(){
	//Calls the destroy function in the active GameState so that the GameState can clean itself up
	Active->Destroy();

	//Delete the active GameState from memory
	delete Active;

	//Clear any remaining debug strings
	DebugStrings.clear();

	//Allegro destroys
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();

	//remove the temporary info file
	remove("temp.temp");

	//Finally, delete the GEngine instance of Engine
	delete this;
}

bool Engine::ShouldTick(){
	return !bExit;
}
bool Engine::ShouldRedraw(){
	return bRedraw;
}

void Engine::Quit(){
	Engine::bExit = true;
}

void Engine::HandleInput(ALLEGRO_EVENT* ev){
	if (!LockedComponent){
		Active->HandleEvents(ev);
	}
	else{
		LockedComponent->handleKeyInput(ev);
	}
	
}

void Engine::Tick(float delta){
	al_get_mouse_state(&mouse_state);
	al_get_keyboard_state(&keyboard_state);
	Active->Tick(delta);

	//Counts the duration of debug outputs and deletes them once they have been on screen for their allotted time
	for (int i = 0; i < (int)DebugStrings.size(); i++){
		DebugStrings[i].elapsedTime += delta;
		if (DebugStrings[i].elapsedTime >= DebugStrings[i].duration){
			DebugStrings.erase(DebugStrings.begin() + i);
		}
	}

	bRedraw = true;
}

void Engine::Draw(){
	Active->Draw();
	bRedraw = false;
	//DrawFPS(delta);

	//Draws debug outputs onto the screen
	for (int i = 0; i < (int)DebugStrings.size(); i++){
		al_draw_textf(debug_font, al_map_rgb(0, 0, 0), 6, i * 16 + 50, ALLEGRO_ALIGN_LEFT, "%s", DebugStrings[i].output);
		al_draw_textf(debug_font, DebugStrings[i].color, 5, i * 16 + 49, ALLEGRO_ALIGN_LEFT, "%s", DebugStrings[i].output);
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

int Engine::GetDisplayWidth(){
	return al_get_display_width(display);
}

int Engine::GetDisplayHeight(){
	return al_get_display_height(display);
}

void Engine::LockInputToUIComponent(UIComponent *c){
	LockedComponent = c;
}

bool Engine::IsInputLocked(){
	return LockedComponent;
}

void Engine::ReleaseInput(){
	LockedComponent = NULL;
}

GameState* Engine::GetCurrentGameState(){
	return Active;
}

void Engine::PrintDebugText(ALLEGRO_COLOR c, float duration, const char* text){
	DebugStrings.push_back(DebugOutput(c, text, duration));
}

void Engine::DrawHitbox(std::vector<Character*> &C){
	for (int i = 0; i < (int)C.size(); i++){
		al_draw_rectangle(C[i]->position.x + C[i]->CollisionBounds.position.x, C[i]->position.y + C[i]->CollisionBounds.position.y, C[i]->position.x + C[i]->CollisionBounds.position.x + C[i]->CollisionBounds.size.x, C[i]->position.y + C[i]->CollisionBounds.position.y + C[i]->CollisionBounds.size.y, BLUE500, 1);
	}
}