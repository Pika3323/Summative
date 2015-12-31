#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(ALLEGRO_BITMAP* s, int width, int height, int frames){
	if (s){
		Sheet = s;
	}
	else{
		fprintf(stderr, "Could not load bitmap for spritesheet\n");
		GEngine->Quit();
	}
	FrameHeight = height;
	FrameWidth = width;
	FramesInAnimation = frames;		//all frames in animation
	TotFrameCount = 0;		//counting frames to check for delay
	Delay = 5;			//the delay for the animation
	CurrentFrame = 0;	//holding the current frame
}

void SpriteSheet::PushFrame(){
	//if it is time to update to the next frame in the animation, reset total frame count
	if (++TotFrameCount >= Delay) {
		if (++CurrentFrame >= FramesInAnimation) {		//if it is at the end of the animation, loop again
			CurrentFrame = 0;
		}
		TotFrameCount = 0;
	}

	//Reset to maximum frame if the active frame has gone past the first frame in the sheet
	if (CurrentFrame < 0){
		CurrentFrame = FramesInAnimation;
	}
}

void SpriteSheet::PushFrame(EADirection Direction){
	CurrentFrame += static_cast<int>(Direction);

	//Reset to frame 0 if the active frame has gone beyond the number of frames in the sheet
	if (++TotFrameCount >= Delay) {
		if (CurrentFrame >= FramesInAnimation) {		//if it is at the end of the animation, loop again
			CurrentFrame = 0;
		}
		TotFrameCount = 0;
	}

	//Reset to maximum frame if the active frame has gone past the first frame in the sheet
	if (CurrentFrame < 0){
		CurrentFrame = FramesInAnimation;
	}
}

//Returns a bitmap of the current frame of animation
ALLEGRO_BITMAP* SpriteSheet::GetFrameBitmap(){
	ALLEGRO_BITMAP* temp = al_create_bitmap(FrameWidth, FrameHeight);

	if (temp){
		al_set_target_bitmap(temp);
		al_draw_bitmap_region(Sheet, FrameWidth * CurrentFrame, 0, FrameWidth, FrameHeight, 0, 0, 0);

		//al_clear_to_color(al_map_rgb(255, 0, 255));
		//Reset target bitmap to display
		al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

		return temp;
	}
	else{
		fprintf(stderr, "Could not access temporary sprite bitmap\n");
		GEngine->Quit();
		return NULL;
	}
	
}

SpriteSheet::~SpriteSheet(){
	//Apparently al_destroy_bitmap() doesn't work...
	Sheet = NULL;
}