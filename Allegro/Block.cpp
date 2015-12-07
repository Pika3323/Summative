#include "Block.h"

Block::Block(Vector2D pos, EBlockType t){
	position = pos;
	type = t;
}

BlockType::BlockType(const char n[16], ALLEGRO_BITMAP* tex){
	strcpy(name, n);
	texture = tex;
}
