#include "Buffer.h"

Buffer::Buffer(ALLEGRO_BITMAP* i, Vector2D ofs, Vector2D d){
	image = i;			//setting all basic information about the buffer
	offset = ofs;
	delta = d;
}