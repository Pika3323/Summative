#include "Dankey.h"

Dankey::Dankey(Vector2D pos){
	position = pos;
	ActualHeight = 64;
	ActualWidth = 64;
	velocity = Vector2D(0.f, 0.f);
	toss = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey throw_e.png"), 64, 64, 8);
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey idle_e.png"), 64, 64, 5);
}

void Dankey::Tick(float delta, Player* player, World* Current){
	if (InRange(player->position.x, position.x - 320, position.x + 320) && Current->bPlay) {
		texture = toss.GetFrameBitmap();
		toss.PushFrame();
	}
	else if (!InRange(player->position.x, position.x - 320, position.x + 320) && Current->bPlay) {
		texture = still.GetFrameBitmap();
		still.PushFrame();
	}
	else if (!Current->bPlay) {
		texture = still.GetFrameBitmap();
		still.PushFrame();
	}
}