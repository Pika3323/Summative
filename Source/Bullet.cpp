#include "Bullet.h"

Bullet::Bullet(Vector2D pos){
	position = pos;
	bullet = SpriteSheet(al_load_bitmap("Textures/Objects/bullet.png"), 16, 16, 4);
	explode = SpriteSheet(al_load_bitmap("Textures/Objects/bulletex.png"), 16, 16, 3);
	ActualHeight = 16;
	ActualWidth = 16;
	texture = al_create_bitmap(ActualWidth, ActualHeight);
	velocity = Vector2D(30.f, 0.f);
}
void Bullet::Tick(float delta, std::vector<Character*> *Curr) {
	if (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->Blocks[(int)((this->position.x + this->ActualWidth) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)][(int)((this->position.y + (this->ActualHeight / 2)) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)].bSpawned
		&& dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->Blocks[(int)((this->position.x + this->ActualWidth) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)][(int)((this->position.y + (this->ActualHeight / 2)) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)].bCollision){
		explode.GetFrameBitmap(this->texture);
		explode.PushFrame();
		if (explode.CurrentFrame == 3){
			delete this;
		}
	}
	else if (dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->Blocks[(int)((this->position.x + this->ActualWidth) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)][(int)((this->position.y + (this->ActualHeight / 2)) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)].bSpawned
		&& !dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->Blocks[(int)((this->position.x + this->ActualWidth) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)][(int)((this->position.y + (this->ActualHeight / 2)) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)].bCollision){
		bullet.GetFrameBitmap(this->texture);
		explode.PushFrame();
		position += velocity;
	}
	else if (!dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->Blocks[(int)((this->position.x + this->ActualWidth) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)][(int)((this->position.y + (this->ActualHeight / 2)) / dynamic_cast<PlayState*>(GEngine->GetCurrentGameState())->CurrentWorld->gridSize)].bSpawned){
		bullet.GetFrameBitmap(this->texture);
		explode.PushFrame();
		position += velocity;
	}
}

void Bullet::Run(Vector2D velocity){

}
void Bullet::Die(){

}