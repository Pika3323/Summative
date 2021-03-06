#include "Bullet.h"

Bullet::Bullet(Vector2D pos, ECharacterDirection d){
	direction = d;
	position = pos;
	bullet = SpriteSheet(al_load_bitmap("Textures/Objects/bullet.png"), 16, 16, 4);
	ActualHeight = 16;
	ActualWidth = 16;
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	if (direction == ECharacterDirection::R_Left)
		velocity = Vector2D(-30.f, 0.f);
	else if (direction == ECharacterDirection::R_Right)
		velocity = Vector2D(30.f, 0.f);

}
void Bullet::Tick(float delta, std::vector<Character*> *Curr) {
	bullet.GetFrameBitmap(this->texture);
	bullet.PushFrame();
}

void Bullet::Run(Vector2D velocity){}
void Bullet::Die(){}
void Bullet::Jump(){}
void Bullet::Collide(Character* OtherCharacter){}
void Bullet::BlockCollide(bool w, int CollisionDirection){}