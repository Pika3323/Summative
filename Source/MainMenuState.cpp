#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(){
	BPlayGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 150, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 90), 0, "PLAY GAME", &MainMenu::PlayGame);
	BEditorGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 54), 0, "TEST CURL", &MainMenu::LoadEditor);
	BOptions = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 18), 0, "OPTIONS", &MainMenu::OpenSettings);
	BExit = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 + 18), 0, "EXIT", &GEngine->Quit);
	BFullscreen = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 + 54), 0, "TOGGLE FULLSCREEN", &MainMenu::ToggleFullscreen);

	t = TextBox(BLUE500, al_map_rgb(33, 33, 33), 100, 72, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, 0), 1, "Test");

	AllUIComponents[0] = &BPlayGame;
	AllUIComponents[1] = &BEditorGame;
	AllUIComponents[2] = &BOptions;
	AllUIComponents[3] = &BExit;
	AllUIComponents[4] = &BFullscreen;
	AllUIComponents[5] = &t;
}

void MainMenuState::Init(){
	printf("Switched to the menu!\n");
}

void MainMenuState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		switch (ev->mouse.button){
		case MOUSE_LB:
			for (int i = 0; i < 6; i++){
				if (InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
					AllUIComponents[i]->onMouseDown();
					break;
				}
				else {
					AllUIComponents[i]->onMouseUp();
				}
			}
		}
	}
}

void MainMenuState::Tick(float delta){
	for (int i = 0; i < 6; i++){
		if (InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
			AllUIComponents[i]->onHoverIn();
		}
		else {
			AllUIComponents[i]->onHoverOut();
		}
	}
}

void MainMenuState::Draw(){
	//Draws the buttons to the screen
	al_clear_to_color(al_map_rgb(250, 250, 250));
	for (int i = 0; i < 6; i++){
		AllUIComponents[i]->Draw();
	}
	t.Draw();
}

void MainMenuState::Destroy(){
	//Reset the system cursor to the default cursor
	al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

void MainMenuState::Pause(){

}

void MainMenuState::Resume(){

}

MainMenuState::~MainMenuState(){

}

void MainMenu::PlayGame(){
	GEngine->ChangeGameState<PlayState>();
}

void MainMenu::LoadEditor(){
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl){
		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/test.php");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "testValue=Derek\n");

		res = curl_easy_perform(curl);

		if (res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

void MainMenu::OpenSettings(){
	printf("Open the settings\n");
}

void MainMenu::ToggleFullscreen(){
	if (!dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->bFullscreen){
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_FULLSCREEN, true);
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_NOFRAME, true);
		al_resize_display(GEngine->GetDisplay(), GEngine->GetDisplayData().width, GEngine->GetDisplayData().height);
		al_set_window_position(GEngine->GetDisplay(), 0, 0);
		dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->bFullscreen = true;
	}
	else{
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_FULLSCREEN, false);
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_NOFRAME, false);
		al_resize_display(GEngine->GetDisplay(), GEngine->GetDisplayWidth(), GEngine->GetDisplayHeight());
	}
}