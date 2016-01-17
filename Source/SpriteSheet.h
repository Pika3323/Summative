#pragma once

#include "Engine.h"

//An enum representing the directions in which an animation can move
enum class EADirection{
	D_Back = -1,
	D_Forward = 1
};

//A class representing a bitmap containing several frames of animation
class SpriteSheet{
public:
	//Moves to the next frame of animation
	void PushFrame();
	void PushFrame(EADirection Direction);

	//in public for evaluating purposes
	int CurrentFrame;

	//Draws the current frame of the spritesheet to the Target bitmap
	void GetFrameBitmap(ALLEGRO_BITMAP* Target);

	SpriteSheet(){}

	SpriteSheet(ALLEGRO_BITMAP* Sheet, int width, int height, int frames);

	~SpriteSheet();
protected:
	//Height of a frame
	int FrameHeight;

	//Width of a frame
	int FrameWidth;
	
	//Elapsed number of frames
	int TotFrameCount;

	//Delay between frames (in ticks)
	int Delay;

	//Number of frames in the animation
	int FramesInAnimation;

	//Bitmap containing the frames of the animation
	ALLEGRO_BITMAP* Sheet;
};