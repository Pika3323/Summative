#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(ALLEGRO_BITMAP* s, int width, int height, int frames){
	Sheet = s;
	FrameHeight = height;
	FrameWidth = width;
	FrameCount = frames;
}

void SpriteSheet::PushFrame(){
	FrameIndex++;
	//Reset to frame 0 if the active frame has gone beyond the number of frames in the sheet
	if (FrameIndex > FrameCount){
		FrameIndex = 0;
	}

	//Reset to maximum frame if the active frame has gone past the first frame in the sheet
	if (FrameIndex < 0){
		FrameIndex = FrameCount;
	}
}

void SpriteSheet::PushFrame(EADirection Direction){
	FrameIndex += static_cast<int>(Direction);

	//Reset to frame 0 if the active frame has gone beyond the number of frames in the sheet
	if (FrameIndex > FrameCount){
		FrameIndex = 0;
	}

	//Reset to maximum frame if the active frame has gone past the first frame in the sheet
	if (FrameIndex < 0){
		FrameIndex = FrameCount;
	}
}

//Returns a bitmap of the current frame of animation
ALLEGRO_BITMAP* SpriteSheet::GetFrameBitmap(){
	ALLEGRO_BITMAP* temp = al_create_bitmap(FrameWidth, FrameHeight);

	al_set_target_bitmap(temp);
	al_draw_bitmap_region(Sheet, FrameWidth * FrameIndex, 0, FrameWidth, FrameHeight, 0, 0, 0);
	//Reset target bitmap to display
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	return temp;
}