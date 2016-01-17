#include "Barrel.h"

Barrel::Barrel(ECharacterDirection d, Vector2D pos){
	Damage = 1.f;
	bOnGround = true;
	ActualWidth = 16;
	ActualHeight = 32;
	position = pos;
	Roll = SpriteSheet(al_load_bitmap("Textures/Objects/Dankeybarrel_e.png"), 16, 32, 8);
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	direction = d;
	if (direction == ECharacterDirection::R_Left)
		velocity = Vector2D(-5.f, 0.f);
	else
		velocity = Vector2D(5.f, 0.f);
	this->SetupCharacterCollision(Vector2D(0.f, 16.f), Vector2D(16.f, 16.f));
}

void Barrel::Tick(float delta, std::vector<Character*> *Curr){
	if (direction == ECharacterDirection::R_Left)
		velocity.x = -5.f;
	else
		velocity.x = 5.f;
	Roll.GetFrameBitmap(this->texture);
	Roll.PushFrame();
}

void Barrel::Run(Vector2D velocity){

}

void Barrel::Jump(){

}

void Barrel::Die(){
	delete this;
}

void Barrel::Collide(Character* OtherCharacter){
	if (dynamic_cast<Player*>(OtherCharacter)){
		OtherCharacter->Health -= this->Damage;
	}
	if (dynamic_cast<Cinas*>(OtherCharacter)){
		OtherCharacter->Health -= this->Damage;
	}
}

void Barrel::BlockCollide(bool w, ECollisionDirection direction){
	if (direction == ECollisionDirection::Right || direction == ECollisionDirection::Left){
		this->velocity.x = 0;
	}

	else if (direction == ECollisionDirection::Top){
		velocity.y = 0;
		position.y += 32.f;
	}

	else if (direction == ECollisionDirection::DownStay){
		bOnGround = true;
		velocity.y = 0;
	}

	else if (direction == ECollisionDirection::DownStop){
		bOnGround = false;
	}
}
