#include "BulletEx.h"

BulletEx::BulletEx(Vector2D pos, ECharacterDirection d){
	Deleted = false;
	direction = d;
	position = pos;
	explode = SpriteSheet(al_load_bitmap("Textures/Objects/bulletex.png"), 16, 16, 3);
	ActualWidth = 16;
	ActualHeight = 16;
	texture = al_create_bitmap(ActualWidth, ActualHeight);
}

void BulletEx::Tick(float delta, std::vector<Character*> *Curr){
	explode.GetFrameBitmap(this->texture);
	explode.PushFrame();
}

void BulletEx::Jump(){

}
void BulletEx::Run(Vector2D velocity){

}
void BulletEx::Die(){

}
