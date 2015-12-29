#pragma once

#include "Engine.h"

//An enum representing the directions in which an animation can move
enum class EADirection{
	D_Back = -1,
	D_Forward = 1
};

class SpriteSheet{
public:
	void PushFrame();
	void PushFrame(EADirection Direction);
	ALLEGRO_BITMAP* GetFrameBitmap();

	SpriteSheet(){ Sheet = NULL; }

	SpriteSheet(ALLEGRO_BITMAP* Sheet, int width, int height, int frames);

	~SpriteSheet();
protected:
	int FrameHeight;
	int FrameWidth;

	int TotFrameCount;
	int Delay;
	int CurrentFrame;
	int FramesInAnimation;

	ALLEGRO_BITMAP* Sheet;
};