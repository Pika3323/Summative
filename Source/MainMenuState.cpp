#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(){
	AllUIComponents[0] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 150, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 90), 0, "PLAY GAME", &MainMenu::PlayGame);
	AllUIComponents[1] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 54), 0, "TEST CURL", &PushLevel);
	AllUIComponents[2] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 18), 0, "OPTIONS", &MainMenu::OpenSettings);
	AllUIComponents[3] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 + 18), 0, "EXIT", &GEngine->Quit);
	AllUIComponents[4] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 + 54), 0, "TOGGLE FULLSCREEN", &MainMenu::ToggleFullscreen);
	AllUIComponents[5] = new TextBox(BLUE500, al_map_rgb(33, 33, 33), 500, 72, Vector2D(GEngine->GetDisplayWidth() / 2 - 250, 0), 1, "Test");
	ActiveScreen = 0;
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
	bool bIsHoverComponent = false;
	UIComponent* HoveredComponent = NULL;
	for (int i = 0; i < 6; i++){
		if (InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
			AllUIComponents[i]->onHoverIn();
		}
		else {
			AllUIComponents[i]->onHoverOut();
		}
		if (InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
			HoveredComponent = AllUIComponents[i];
			bIsHoverComponent = true;
		}
	}
	if (bIsHoverComponent) {
		al_set_system_mouse_cursor(GEngine->GetDisplay(), HoveredComponent->cursor);
	}
	else {
		al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}
}

void MainMenuState::Draw(){
	al_clear_to_color(al_map_rgb(250, 250, 250));
	if (ActiveScreen == 0){
		for (int i = 0; i < 6; i++){
			AllUIComponents[i]->Draw();
		}
	}
	else if (ActiveScreen = 1){

	}
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

		for (int i = 0; i < 6; i++) {
			dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->position.x = GEngine->GetDisplayWidth() / 2 - dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->width / 2;
		}
	}
	else{
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_FULLSCREEN, false);
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_NOFRAME, false);
		al_resize_display(GEngine->GetDisplay(), 1280, 720);
		dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->bFullscreen = false;
		for (int i = 0; i < 6; i++) {
			dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->position.x = GEngine->GetDisplayWidth() / 2 - dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->width / 2;
		}
	}
}

void PushLevel(){
	char level[64];
	printf("Upload level:");
	scanf("%s", level);

	strcat(level, ".bvl");

	FILE* fd;

	fd = fopen(level, "rb");
	if (!fd){
		fprintf(stderr, "Could not open %s\n", level);
		return;
	}
	fseek(fd, 0L, SEEK_END);
	int sz = ftell(fd);
	fseek(fd, 0L, SEEK_SET);

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	/* Fill in the file upload field */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelfile",
		CURLFORM_FILE, level,
		CURLFORM_END);

	/* Fill in the filename field */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "username",
		CURLFORM_COPYCONTENTS, "TestUser",
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelname",
		CURLFORM_COPYCONTENTS, "Other Test",
		CURLFORM_END);


	/* Fill in the submit field too, even if this is rarely needed */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		/* what URL that receives this POST */

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/PostNewLevel");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);

		/* then cleanup the formpost chain */
		curl_formfree(formpost);
		/* free slist */
		curl_slist_free_all(headerlist);
	}
}