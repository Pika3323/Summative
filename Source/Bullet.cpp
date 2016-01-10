#include "Bullet.h"

Bullet::Bullet(Vector2D pos){
	position = pos;
	bullet = SpriteSheet(al_load_bitmap("Textures/Objects/bullet.png"), 16, 16, 4);
	ActualHeight = 16;
	ActualWidth = 16;
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	velocity = Vector2D(30.f, 0.f);
}
void Bullet::Tick(float delta, std::vector<Character*> *Curr) {
	bullet.GetFrameBitmap(this->texture);
	bullet.PushFrame();
	position += velocity;
}

void Bullet::Run(Vector2D velocity){}
void Bullet::Die(){}
void Bullet::Jump(){}