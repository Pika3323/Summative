#include "Block.h"

Block::Block(Vector2D pos, EBlockType t, int D){
	position = pos;
	type = t;
	Direction = D;
}

void Block::Draw(ALLEGRO_BITMAP* typeTex){
	switch (Direction) {
	case 0:
		al_draw_bitmap(typeTex, position.x, position.y, ALLEGRO_VIDEO_BITMAP);
		break;
	case 1:
		al_draw_bitmap(typeTex, position.x, position.y, ALLEGRO_VIDEO_BITMAP + ALLEGRO_FLIP_HORIZONTAL);
		break;
	case 2:
		al_draw_bitmap(typeTex, position.x, position.y, ALLEGRO_VIDEO_BITMAP + ALLEGRO_FLIP_VERTICAL);
		break;
	case 3:
		al_draw_bitmap(typeTex, position.x, position.y, ALLEGRO_VIDEO_BITMAP + ALLEGRO_FLIP_VERTICAL + ALLEGRO_FLIP_HORIZONTAL);
		break;
	}
	
}

BlockType::BlockType(const char n[16], ALLEGRO_BITMAP* tex, bool collision, bool d){
	bCollision = collision;			//sets whether or not this block is a collidable block
	bRandomD = d;
	strcpy(name, n);
	if (tex) {
		texture = tex;
	}
	else {
		fprintf(stderr, "Could not load BlockType texture\n");
		GEngine->Quit();
	}
}