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
	dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->ActiveScreen = 1;
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
#define LOCAL_FILE      "VersionTest.bvl"
#define UPLOAD_FILE_AS  "Level.bvl"
#define REMOTE_URL      "ftp://llamabagel.ca./blocks/Levels/Files/"  UPLOAD_FILE_AS
#define RENAME_FILE_TO  "1.bvl"

	CURL *curl;
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;

	struct curl_slist *headerlist = NULL;
	static const char buf_1[] = "RNFR " UPLOAD_FILE_AS;
	static const char buf_2[] = "RNTO " RENAME_FILE_TO;

	/* get the file size of the local file */
	if (stat(LOCAL_FILE, &file_info)) {
		printf("Couldnt open '%s': %s\n", LOCAL_FILE, strerror(errno));
		return;
	}
	fsize = (curl_off_t)file_info.st_size;

	printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);

	/* get a FILE * of the same file */
	hd_src = fopen(LOCAL_FILE, "rb");

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* build a list of commands to pass to libcurl */
		headerlist = curl_slist_append(headerlist, buf_1);
		headerlist = curl_slist_append(headerlist, buf_2);

		/* we want to use our own read function */
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		/* specify target */
		curl_easy_setopt(curl, CURLOPT_URL, REMOTE_URL);

		/* pass in that last of FTP commands to run after the transfer */
		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

		/* now specify which file to upload */
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

		/* Set the size of the file to upload (optional).  If you give a *_LARGE
		option you MUST make sure that the type of the passed-in argument is a
		curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
		make sure that to pass in a type 'long' argument. */
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
			(curl_off_t)fsize);

		/* Now run off and do what you've been told! */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		/* clean up the FTP commands list */
		curl_slist_free_all(headerlist);

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	fclose(hd_src); /* close the local file */

	curl_global_cleanup();
}