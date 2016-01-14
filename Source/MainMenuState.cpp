#include "MainMenuState.h"
#include "PlayState.h"
#include "LevelSelectState.h"

MainMenuState::MainMenuState(){
	AllUIComponents[0] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 150, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 90), 0, "PLAY GAME", &MainMenu::PlayGame);
	AllUIComponents[1] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 54), 0, "VIEW LEVELS", &PushLevel);
	AllUIComponents[2] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 - 18), 0, "OPTIONS", &MainMenu::LoadEditor);
	AllUIComponents[3] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 + 18), 0, "EXIT", &GEngine->Quit);
	AllUIComponents[4] = new Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 200, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 100, GEngine->GetDisplayHeight() / 2 + 54), 0, "TOGGLE FULLSCREEN", &MainMenu::ToggleFullscreen);
	//AllUIComponents[5] = new TextBox(BLUE500, al_map_rgb(33, 33, 33), 500, 72, Vector2D(GEngine->GetDisplayWidth() / 2 - 250, 0), 1, "Test");
	ActiveScreen = 0;
	LargeRoboto = al_load_ttf_font("Roboto-Regular.ttf", 48, 0);
	Background[0] = Buffer(al_load_bitmap("Textures/Scenes/Background_Gauss.png"), Vector2D(0, 0), Vector2D(0, 0));
	Background[1] = Buffer(al_load_bitmap("Textures/Scenes/Background_Gauss.png"), Vector2D(1024, 0), Vector2D(0, 0));
	Background[2] = Buffer(al_load_bitmap("Textures/Scenes/Background_Gauss.png"), Vector2D(1024, 0), Vector2D(0, 0));


}

void MainMenuState::Init(){
	printf("Switched to the menu!\n");
}

void MainMenuState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		switch (ev->mouse.button){
		case MOUSE_LB:
			for (int i = 0; i < 5; i++){
				if (IMath::InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && IMath::InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
					AllUIComponents[i]->onMouseDown();
					break;
				}
				else {
					AllUIComponents[i]->onMouseUp();
				}
			}
		}
	}
	else if (ev->type == ALLEGRO_EVENT_KEY_DOWN){
		switch (ev->keyboard.keycode){
		case ALLEGRO_KEY_ESCAPE:
			GEngine->Quit();
			break;
		}
	}
}

void MainMenuState::Tick(float delta){
	bool bIsHoverComponent = false;
	UIComponent* HoveredComponent = NULL;
	for (int i = 0; i < 5; i++){
		if (IMath::InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && IMath::InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
			AllUIComponents[i]->onHoverIn();
		}
		else {
			AllUIComponents[i]->onHoverOut();
		}
		if (IMath::InRange(GEngine->GetMouseState().x, AllUIComponents[i]->position.x, AllUIComponents[i]->position.x + AllUIComponents[i]->width) && IMath::InRange(GEngine->GetMouseState().y, AllUIComponents[i]->position.y, AllUIComponents[i]->position.y + AllUIComponents[i]->height)){
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
	for (int i = 0; i < 3; i++) {
		Background[i].offset.x -= 5.f;
		if (Background[0].offset.x < -1024){
			Background[0].offset.x = 0;
			Background[1].offset.x = 1024;
			Background[2].offset.x = 2048;
		}
	}
}

void MainMenuState::Draw(){
	al_clear_to_color(al_map_rgb(250, 250, 250));
	for (int i = 0; i < 3; i++) {
		al_draw_bitmap(Background[i].image, Background[i].offset.x, Background[i].offset.y, 0);
	}
	al_draw_text(LargeRoboto, al_map_rgb(100, 100, 100), GEngine->GetDisplayWidth() / 2, 132, ALLEGRO_ALIGN_CENTER, "The Block Game");
	if (ActiveScreen == 0){
		for (int i = 0; i < 5; i++){
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
	Online::PostLevel("Seanisdumb");
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

		for (int i = 0; i < 5; i++) {
			dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->position.x = GEngine->GetDisplayWidth() / 2 - dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->width / 2;
		}
	}
	else{
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_FULLSCREEN, false);
		al_set_display_flag(GEngine->GetDisplay(), ALLEGRO_NOFRAME, false);
		al_resize_display(GEngine->GetDisplay(), 1280, 720);
		dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->bFullscreen = false;
		for (int i = 0; i < 5; i++) {
			dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->position.x = GEngine->GetDisplayWidth() / 2 - dynamic_cast<MainMenuState*>(GEngine->GetCurrentGameState())->AllUIComponents[i]->width / 2;
		}
	}
}

void PushLevel(){
	GEngine->ChangeGameState<LevelSelectState>();
}