#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(){
	BPlayGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 150, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 90), 0, "PLAY GAME");
	BEditorGame = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 54), 0, "LEVEL EDITOR");
	BOptions = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 - 18), 0, "OPTIONS");
	BExit = Button(al_map_rgb(250, 250, 250), al_map_rgb(33, 140, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 50, GEngine->GetDisplayHeight() / 2 + 18), 0, "EXIT");
	BPlayGame.onDown = &PlayGame;
	BEditorGame.onDown = &LoadEditor;
	BOptions.onDown = &OpenSettings;
	BExit.onDown = &GEngine->Quit;

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