#pragma once

#include "Engine.h"
#include "World.h"
#include "Buffer.h"
#include "Block.h"

class EditorState : public GameState {
public:
	void Init();

	void Pause();
	void Resume();

	void HandleEvents(ALLEGRO_EVENT *ev);
	void Tick(float delta);
	void Draw();

	void Destroy();

	EditorState();
	~EditorState();
protected:
	World* CurrentWorld;

	Buffer blockBuff;
	Buffer dubBuff;
	Buffer Backgroud;

	Vector2D Clicked;
	GridTile ClickedTile;
	bool bClicked = false;
	EBlockType SelectedBlock = EBlockType::B_Brick;
};