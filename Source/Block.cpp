#include "Block.h"

Block::Block(Vector2D pos, EBlockType t){
	position = pos;
	type = t;
}

void Block::Draw(ALLEGRO_BITMAP* typeTex){
	al_draw_bitmap(typeTex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
}

BlockType::BlockType(const char n[16], ALLEGRO_BITMAP* tex){
	strcpy(name, n);
	texture = tex;
}

