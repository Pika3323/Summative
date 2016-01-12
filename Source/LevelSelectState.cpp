#include "LevelSelectState.h"
bool LevelSelectState::bLocalMenu = true;

LevelSelectState::LevelSelectState(){
	LargeRoboto = al_load_ttf_font("Roboto-Regular.ttf", 24, 0);
	strcpy(Username, "TestUser");
	Components.push_back(new Button(WHITE, BLUE500, 250, 36, Vector2D(GEngine->GetDisplayWidth() / 2 - 250, 0.f), 0, "Local Levels", &ViewLocal));
	Components.push_back(new Button(WHITE, BLUE500, 250, 36, Vector2D(GEngine->GetDisplayWidth() / 2, 0.f), 0, "Online Levels", &ViewOnline));
}

void LevelSelectState::Init(){
	FILE* L = fopen("Levels/Levels.bvla", "rb");
	if (!L){
		L = fopen("Levels/Levels.bvla", "wb+");
		fclose(L);
		L = fopen("Levels/Levels.bvla", "rb");
	}
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
		OnlineTiles.push_back(new List(Vector2D(GEngine->GetDisplayWidth() / 2 - 250, i * 152 + 39), Levels[i]));
	}
}

void LevelSelectState::Draw(){
	al_clear_to_color(WHITE);
	if (bLocalMenu){
		for (int i = 0; i < (int)LocalTiles.size(); i++){
			LocalTiles[i]->Draw();
		}
		if (!(int)LocalTiles.size()){
			al_draw_text(LargeRoboto, al_map_rgb(100, 100, 100), GEngine->GetDisplayWidth() / 2, 100, ALLEGRO_ALIGN_CENTER, "Nothing to see here!");
		}
	}
	else {
		for (int i = 0; i < (int)OnlineTiles.size(); i++){
			OnlineTiles[i]->Draw();
		}
	}

	for (int i = 0; i < (int)Components.size(); i++){
		Components[i]->Draw();
	}
}

void LevelSelectState::Pause(){

}
void LevelSelectState::Resume(){

}

void LevelSelectState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		switch (ev->mouse.button){
		case MOUSE_LB:
			for (int i = 0; i < (int)Components.size(); i++){
				if (InRange(GEngine->GetMouseState().x, Components[i]->position.x, Components[i]->position.x + Components[i]->width) && InRange(GEngine->GetMouseState().y, Components[i]->position.y, Components[i]->position.y + Components[i]->height)){
					Components[i]->onMouseDown();
					break;
				}
				else {
					Components[i]->onMouseUp();
				}
			}

			//Local Tiles
			for (int i = 0; i < (int)LocalTiles.size(); i++){
				if (InRange(GEngine->GetMouseState().x, LocalTiles[i]->position.x, LocalTiles[i]->position.x + LocalTiles[i]->width) && InRange(GEngine->GetMouseState().y, LocalTiles[i]->position.y, LocalTiles[i]->position.y + LocalTiles[i]->height)){
					LocalTiles[i]->onMouseDown();
					break;
				}
			}

			//Online Tiles
			for (int i = 0; i < (int)OnlineTiles.size(); i++){
				if (InRange(GEngine->GetMouseState().x, OnlineTiles[i]->position.x, OnlineTiles[i]->position.x + OnlineTiles[i]->width) && InRange(GEngine->GetMouseState().y, OnlineTiles[i]->position.y, OnlineTiles[i]->position.y + OnlineTiles[i]->height)){
					OnlineTiles[i]->onMouseDown();
					break;
				}
			}
		}
	}
}
void LevelSelectState::Tick(float delta){
	ALLEGRO_MOUSE_STATE newState = GEngine->GetMouseState();
	bool bIsHoverComponent = false;
	UIComponent* HoveredComponent = NULL;
	for (int i = 0; i < (int)Components.size(); i++){
		if (InRange(GEngine->GetMouseState().x, Components[i]->position.x, Components[i]->position.x + Components[i]->width) && InRange(GEngine->GetMouseState().y, Components[i]->position.y, Components[i]->position.y + Components[i]->height)){
			Components[i]->onHoverIn();
		}
		else {
			Components[i]->onHoverOut();
		}
		if (InRange(GEngine->GetMouseState().x, Components[i]->position.x, Components[i]->position.x + Components[i]->width) && InRange(GEngine->GetMouseState().y, Components[i]->position.y, Components[i]->position.y + Components[i]->height)){
			HoveredComponent = Components[i];
			bIsHoverComponent = true;
		}
	}
	if (bIsHoverComponent) {
		al_set_system_mouse_cursor(GEngine->GetDisplay(), HoveredComponent->cursor);
	}
	else {
		al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}

	if (bLocalMenu) {
		for (int i = 0; i < (int)LocalTiles.size(); i++){
			LocalTiles[i]->position.y += (newState.z - mstate.z) * 25;
		}
	}
	else {
		for (int i = 0; i < (int)OnlineTiles.size(); i++){
			OnlineTiles[i]->position.y += (newState.z - mstate.z) * 25;
		}
	}
	mstate = newState;
}

void LevelSelectState::Destroy(){

}
LevelSelectState::~LevelSelectState(){

}

void ViewOnline(){
	LevelSelectState::bLocalMenu = false;
}
void ViewLocal(){
	LevelSelectState::bLocalMenu = true;
}
void PlayLevel(){
	GEngine->ChangeGameState<PlayState>();
}