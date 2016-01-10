#include "List.h"

List::List(){
	height = 150;
	width = 500;
	tex = al_create_bitmap(width, height);
	RobotoSmall = al_load_ttf_font("Roboto-Regular.ttf", 10, 0);
	RobotoMedium = al_load_ttf_font("Roboto-Regular.ttf", 16, 0);
	RobotoLarge = al_load_ttf_font("Roboto-Regular.ttf", 24, 0);
	Play = Button(WHITE, BLUE500, 100, 32, Vector2D(6.f, 64.f), 0, "PLAY", &PlayGame);
}

List::List(Vector2D pos, WorldLevelData l){
	height = 150;
	width = 500;
	tex = al_create_bitmap(width, height);
	RobotoSmall = al_load_ttf_font("Roboto-Regular.ttf", 10, 0);
	RobotoMedium = al_load_ttf_font("Roboto-Regular.ttf", 16, 0);
	RobotoLarge = al_load_ttf_font("Roboto-Regular.ttf", 24, 0);
	Play = Button(WHITE, BLUE500, 100, 32, Vector2D(6.f, 64.f), 0, "PLAY", &PlayGame);
	Level = l;
	position = pos;
	al_set_target_bitmap(tex);
	al_clear_to_color(BLUE500);
	al_draw_textf(RobotoLarge, WHITE, 6, 6, 0, "%s", Level.Name);
	al_draw_textf(RobotoSmall, WHITE, 6, 32, 0, "%s", Level.Creator);
	if (Level.Completions && Level.Attempts){
		al_draw_textf(RobotoMedium, WHITE, 6, height - 24, 0, "Completion rate: %d%%", Level.Completions / Level.Attempts);
	}
	else {
		al_draw_textf(RobotoMedium, WHITE, 6, height - 24, 0, "Completion rate: %s%%", "NaN");
	}
	

	al_draw_textf(RobotoMedium, WHITE, width - 64, 64, ALLEGRO_ALIGN_CENTER, "Up: %d", Level.Upvotes);
	al_draw_textf(RobotoMedium, WHITE, width - 64, 76, ALLEGRO_ALIGN_CENTER, "Down: %d", Level.Downvotes);
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}

void List::handleKeyInput(ALLEGRO_EVENT *ev){

}

void List::onHoverIn(){

}

void List::onHoverOut(){

}

void List::onMouseDown(){

}

void List::onMouseUp(){

}

void List::Draw(){
	al_draw_bitmap(tex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}

void PlayGame(){
	GEngine->ChangeGameState<PlayState>();
	PlayState *NewState = dynamic_cast<PlayState *>(GEngine->GetCurrentGameState());
	if (NULL != NewState)
	{
		printf("Uhh, the game state");
	}
}