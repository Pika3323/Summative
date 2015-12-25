#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(ALLEGRO_BITMAP* s, int width, int height, int frames){
	Sheet = s;
	FrameHeight = height;
	FrameWidth = width;
	FramesInAnimation = frames;
	TotFrameCount = 0;
	Delay = 5;
	CurrentFrame = 0;
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

	al_set_target_bitmap(temp);
	al_draw_bitmap_region(Sheet, FrameWidth * CurrentFrame, 0, FrameWidth, FrameHeight, 0, 0, 0);
	//Reset target bitmap to display
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	return temp;
}