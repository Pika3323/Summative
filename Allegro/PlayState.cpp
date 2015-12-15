#include "PlayState.h"

PlayState::PlayState(){
	
	CurrentWorld = new World(Vector2D(4096.f, 2048.f), 32);
	Character TinTin = Character(Vector2D(0, 0), 64, 128);	//TinTin character
	Gravity CurrentGrav = Gravity(Vector2D(0.f, 5.f));		//current world gravity
	Buffer notPlayingBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f)); //block buffer for when not playing
	Buffer blockBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//play buffer for blocks
	Buffer dubBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//buffer for grid
	Buffer Background = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(2.5f, 2.5f));	//buffer for background

	CurrentWorld->bPlay = false;
}