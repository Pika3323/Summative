#include "Buffer.h"

Buffer::Buffer(ALLEGRO_BITMAP* i, Vector2D ofs, Vector2D d){
	image = i;
	offset = ofs;
	delta = d;
}