#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(){
	BPlayGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 150, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 90), 0, "PLAY GAME", &PlayGame);
	BEditorGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 54), 0, "LEVEL EDITOR", &LoadEditor);
	BOptions = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 18), 0, "OPTIONS", &OpenSettings);
	BExit = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 + 18), 0, "EXIT", &GEngine->Quit);

	AllButtons[0] = &BPlayGame;
	AllButtons[1] = &BEditorGame;
	AllButtons[2] = &BOptions;
	AllButtons[3] = &BExit;
}

void MainMenuState::Init(){
	printf("Switched to the menu!\n");
}

void MainMenuState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		switch (ev->mouse.button){
		case MOUSE_LB:
			for (int i = 0; i < 4; i++){
				if (InRange(GEngine->GetMouseState().x, AllButtons[i]->position.x, AllButtons[i]->position.x + AllButtons[i]->width) && InRange(GEngine->GetMouseState().y, AllButtons[i]->position.y, AllButtons[i]->position.y + AllButtons[i]->height)){
					AllButtons[i]->onMouseDown();
					break;
				}
				else {
					AllButtons[i]->onMouseUp();
					//break;
				}
			}
		}
	}
}

void MainMenuState::Tick(){
	for (int i = 0; i < 4; i++){
		if (InRange(GEngine->GetMouseState().x, AllButtons[i]->position.x, AllButtons[i]->position.x + AllButtons[i]->width) && InRange(GEngine->GetMouseState().y, AllButtons[i]->position.y, AllButtons[i]->position.y + AllButtons[i]->height)){
			AllButtons[i]->onHoverIn();
			break;
		}
		else {
			AllButtons[i]->onHoverOut();
		}
	}
}

void MainMenuState::Draw(){
	al_clear_to_color(al_map_rgb(250, 250, 250));
	for (int i = 0; i < 4; i++){
		AllButtons[i]->Draw();
	}
}

void MainMenuState::Destroy(){
	al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
}

void MainMenuState::Pause(){

}

void MainMenuState::Resume(){

}

MainMenuState::~MainMenuState(){

}

void PlayGame(){
	GEngine->ChangeGameState<PlayState>();
}

void LoadEditor(){
	printf("Load the editor\n");
}

void OpenSettings(){
	printf("Open the settings\n");
}