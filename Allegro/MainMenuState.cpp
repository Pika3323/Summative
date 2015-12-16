#include "MainMenuState.h"

MainMenuState::MainMenuState(){
	BPlayGame = Button(al_map_rgb(255, 255, 255), al_map_rgb(33, 150, 243), 100, 36, Vector2D(GEngine->GetDisplayWidth() / 2, 0), 0, "PLAY GAME", GEngine->GetDisplay());
}

void MainMenuState::Init(){
	printf("Switched to the menu!\n");
}

void MainMenuState::HandleEvents(ALLEGRO_EVENT *ev){

}

void MainMenuState::Tick(){

}

void MainMenuState::Draw(){
	BPlayGame.draw();
}

void MainMenuState::Destroy(){

}

void MainMenuState::Pause(){

}

void MainMenuState::Resume(){

}

MainMenuState::~MainMenuState(){

}