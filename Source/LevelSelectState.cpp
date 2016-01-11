#include "LevelSelectState.h"
bool LevelSelectState::bLocalMenu = true;

LevelSelectState::LevelSelectState(){
	strcpy(Username, "TestUser");
	Components.push_back(new Button(WHITE, BLUE500, 250, 32, Vector2D(GEngine->GetDisplayWidth() / 2 - 250, 0.f), 0, "Local Levels", &ToggleList));
	Components.push_back(new Button(WHITE, BLUE500, 250, 32, Vector2D(GEngine->GetDisplayWidth() / 2, 0.f), 0, "Online Levels", &ToggleList));
}

void LevelSelectState::Init(){
	FILE* L = fopen("Levels/Levels.bvla", "rb");

	fseek(L, 0L, SEEK_END);
	int sz = ftell(L);
	fseek(L, 0L, SEEK_SET);

	for (int i = 0; i < sz / (int)sizeof(WorldLevelData); i++) {
		WorldLevelData l;
		fread(&l, sizeof(WorldLevelData), 1, L);
		LocalLevels.push_back(l);
	}


	Online::GetLevelData(Username, Levels);

	for (int i = 0; i < (int)Levels.size(); i++){
		OnlineTiles.push_back(new List(Vector2D(GEngine->GetDisplayWidth() / 2 - 250, i * 152 + 3), Levels[i]));
	}
}

void LevelSelectState::Draw(){
	al_clear_to_color(WHITE);
	for (int i = 0; i < (int)OnlineTiles.size(); i++){
		OnlineTiles[i]->Draw();
	}
}

void LevelSelectState::Pause(){

}
void LevelSelectState::Resume(){

}

void LevelSelectState::HandleEvents(ALLEGRO_EVENT *ev){

}
void LevelSelectState::Tick(float delta){

}

void LevelSelectState::Destroy(){

}
LevelSelectState::~LevelSelectState(){

}

void ToggleList(){
	LevelSelectState::bLocalMenu = !LevelSelectState::bLocalMenu;
}