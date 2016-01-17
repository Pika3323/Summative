#pragma once

#include "Engine.h"

//An enum representing the directions in which an animation can move
enum class EADirection{
	D_Back = -1,
	D_Forward = 1
};

class SpriteSheet{
public:
	void PushFrame();		//making the frames proceed in the animation
	void PushFrame(EADirection Direction);		//this would be used if there were ever a reverse in time

	//in public for evaluating purposes (the animation's current frame)
	int CurrentFrame;

	//Draws the current frame of the spritesheet to the Target bitmap
	void GetFrameBitmap(ALLEGRO_BITMAP* Target);

	SpriteSheet(){}

	SpriteSheet(ALLEGRO_BITMAP* Sheet, int width, int height, int frames);

	~SpriteSheet();
protected:
	int FrameHeight;		//one frame height
	int FrameWidth;			//one frame width
	int TotFrameCount;		//counting the frames that have gone by since last 'Delay' set
	int Delay;				//the delay between switching frames (for this game, it is five)
	int FramesInAnimation;	//the total count of frames in the animation

	ALLEGRO_BITMAP* Sheet;	//the sheet itself
};