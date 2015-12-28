#include "Dankey.h"

Dankey::Dankey(Vector2D pos){
	position = pos;
	ActualHeight = 64;
	ActualWidth = 64;
	velocity = Vector2D(0.f, 0.f);
	toss = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey throw_e.png"), 64, 64, 8);
	still = SpriteSheet(al_load_bitmap("Textures/Characters/Dankey idle_e.png"), 64, 64, 5);
}

void Dankey::Tick(float delta){
	if (InRange(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x, position.x - 320, position.x + 320) && dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		texture = toss.GetFrameBitmap();
		toss.PushFrame();
	}
	else if (!InRange(dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->TinTin->position.x, position.x - 320, position.x + 320) && dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		texture = still.GetFrameBitmap();
		still.PushFrame();
	}
	else if (!dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->bPlay) {
		texture = still.GetFrameBitmap();
		still.PushFrame();
	}
}

void Dankey::Run(Vector2D velocity){

}

void Dankey::Jump(){

}

void Dankey::Die(){

}