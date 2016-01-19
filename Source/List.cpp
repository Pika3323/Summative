#include "List.h"

List::List(){
	height = 150;
	width = 500;
	tex = al_create_bitmap(width, height);
	RobotoSmall = al_load_ttf_font("Roboto-Regular.ttf", 10, 0);
	RobotoMedium = al_load_ttf_font("Roboto-Regular.ttf", 16, 0);
	RobotoLarge = al_load_ttf_font("Roboto-Regular.ttf", 24, 0);
	Play = Button(WHITE, BLUE500, 100, 36, Vector2D(6.f, 64.f), 0, "PLAY", &PlayGame);
}

List::List(Vector2D pos, WorldLevelData l){
	height = 150;
	width = 500;
	tex = al_create_bitmap(width, height);
	RobotoSmall = al_load_ttf_font("Roboto-Regular.ttf", 10, 0);
	RobotoMedium = al_load_ttf_font("Roboto-Regular.ttf", 16, 0);
	RobotoLarge = al_load_ttf_font("Roboto-Regular.ttf", 24, 0);
	Play = Button(WHITE, BLUE500, 100, 36, Vector2D(6.f, 64.f), 0, "PLAY", &PlayGame);
	Level = l;
	position = pos;
	al_set_target_bitmap(tex);
	al_clear_to_color(BLUE500);
	al_draw_textf(RobotoLarge, WHITE, 6, 6, 0, "%s", Level.Name);
	al_draw_textf(RobotoSmall, WHITE, 6, 32, 0, "%s", Level.Creator);
	if (Level.Completions && Level.Attempts){
		al_draw_textf(RobotoMedium, WHITE, 6, height - 24, 0, "Completion rate: %.2f%%", ((float)Level.Completions / (float)Level.Attempts) * 100);
	}
	else {
		al_draw_textf(RobotoMedium, WHITE, 6, height - 24, 0, "Completion rate: %s%%", "NaN");
	}
	al_draw_textf(RobotoSmall, al_map_rgba(255, 255, 255, 100), width - 3, 150 - 16, ALLEGRO_ALIGN_RIGHT, "%s", Level.Date);
	
	Play.Draw();
	al_draw_textf(RobotoMedium, WHITE, width - 64, 64, ALLEGRO_ALIGN_CENTER, "Completions: %d", Level.Completions);
	al_draw_textf(RobotoMedium, WHITE, width - 64, 76, ALLEGRO_ALIGN_CENTER, "Attempts: %d", Level.Attempts);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}

void List::handleKeyInput(ALLEGRO_EVENT *ev){

}

void List::onHoverIn(){

}

void List::onHoverOut(){

}

void List::onMouseDown(){
	ALLEGRO_MOUSE_STATE mstate = GEngine->GetMouseState();
	Vector2D Relative = Vector2D(mstate.x, mstate.y) - position;
	if (IMath::InRange(Relative.x, Play.position.x, Play.position.x + Play.width) && IMath::InRange(Relative.y, Play.position.y, Play.position.y + Play.height)) {
		Online::GetLevel(Level.id);
		GEngine->SharedVar.bLoadingLevel = true;
		strcpy(GEngine->SharedVar.LoadLevelName, Level.Name);
		GEngine->SharedVar.id = Level.id;
		Play.onDown();
	}
}

void List::onMouseUp(){

}

void List::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}

void PlayGame(){
	GEngine->ChangeGameState<PlayState>();
}