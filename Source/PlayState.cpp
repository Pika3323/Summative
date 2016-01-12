#include "PlayState.h"
#include "MainMenuState.h"

PlayState::PlayState(){
	CurrentWorld = new World(Vector2D(4096.f, 2048.f), 32);
	TinTin = new Player(128, 64);	//The main player character
	TinTin->SetCharacterWorldPosition(Vector2D(0.f, 0.f));
	CurrentEffects = new Physics(Vector2D(0.f, 1.f));		//current world gravity
	notPlayingBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f)); //block buffer for when not playing
	BlockBuffer = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//play buffer for blocks
	GridBuffer = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//buffer for grid
	Background = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(2.5f, 2.5f));	//buffer for background

	CurrentWorld->bPlay = false;
	PlayerOldPosition = Vector2D(0.f, 0.f);

	//Load a cursor and check if it loaded properly
	BoxSelectCursor = al_load_bitmap("Textures/Cursor_BoxSelect.png");
	if (!BoxSelectCursor){
		fprintf(stderr, "Could not load cursor\n");
	}

	CircleSelect = al_create_mouse_cursor(BoxSelectCursor, 8, 8);
	CurrentWorld->EnemySelect = false;

	PauseButton = new Button(al_map_rgb(255, 255, 255), BLUE500, 32, 32, Vector2D(0.f, 0.f), 2, "||", &PauseButtonDown);
}

void PlayState::DestroyCharacter(Character* C){
	std::vector<Character*>::iterator it;

	//Finds the character in the character vector
	it = std::find(CurrCharacters.begin(), CurrCharacters.end(), C);

	//Removes the character
	CurrCharacters.erase(it);

	//Deletes character from memory
	delete C;
}

void PlayState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->keyboard.keycode == ALLEGRO_KEY_P && ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		if (!Paused){
			this->Pause();
		}
		else{
			this->Resume();
		}
	}
	if (!Paused) {
		if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev->keyboard.keycode) {
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				if (!CurrentWorld->bPlay){
					WorldMoveDelta.x = -5.f;
				}
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				if (!CurrentWorld->bPlay){
					WorldMoveDelta.x = 5.f;
				}
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				if (!CurrentWorld->bPlay){
					WorldMoveDelta.y = -5.f;
				}
				break;
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				if (CurrentWorld->bPlay){
					TinTin->Jump();
				}
				else{
					WorldMoveDelta.y = 5.f;
				}
				break;
			case ALLEGRO_KEY_C:
				bBoxSelect = !bBoxSelect;
				if (bBoxSelect){
					al_set_mouse_cursor(GEngine->GetDisplay(), CircleSelect);
				}
				else {
					al_set_system_mouse_cursor(GEngine->GetDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
				}
				break;
			case ALLEGRO_KEY_SPACE:
				if (!CurrentWorld->bPlay){
					CurrentWorld->bPlay = true;
					for (int i = 0; i < (int)CurrentWorld->EnemiesStored.size(); i++){
						if (CurrentWorld->EnemiesStored[i].Type == EnemyType::E_Cinas){
							CurrCharacters.push_back(new Cinas(CurrentWorld->EnemiesStored[i].position));
						}
						else if (CurrentWorld->EnemiesStored[i].Type == EnemyType::E_Dankey){
							CurrCharacters.push_back(new Dankey(CurrentWorld->EnemiesStored[i].position));
						}
					}
					TinTin->SetCharacterWorldPosition(CharacterStart);
				}
				else {
					CurrentWorld->bPlay = false;
					CurrCharacters.clear();
					CurrCharacters.push_back(TinTin);
					TinTin->Health = 100.f;
				}
				TinTin->bOnGround = false;
				TinTin->velocity = Vector2D(0.f, 0.f);
				break;
			case ALLEGRO_KEY_ESCAPE:
				GEngine->Quit();
				break;
			case ALLEGRO_KEY_E:
				if (!CurrentWorld->EnemySelect)
					CurrentWorld->EnemySelect = true;
				else if (CurrentWorld->EnemySelect)
					CurrentWorld->EnemySelect = false;
				break;
			case ALLEGRO_KEY_H:
				if (!CurrentWorld->bPlay)
					ChangingStart = true;
				break;
			default:
				break;
			}
		}
		//On KeyUp
		else if (ev->type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev->keyboard.keycode) {
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				WorldMoveDelta.y = 0.f;
				break;
			case ALLEGRO_KEY_M:
				GEngine->ChangeGameState<MainMenuState>();
				break;
			case ALLEGRO_KEY_H:
				ChangingStart = false;
				break;
			default:
				break;
			}
		}
		//On mouse click
		else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			switch (ev->mouse.button){
			case MOUSE_LB:
				if (!CurrentWorld->bPlay && ev->mouse.y < 100) {
					if (ev->mouse.x < 900){
						CurrentWorld->EnemySelect = false;
						SelectedBlock = static_cast<EBlockType>(ev->mouse.x / 100);
					}
					else if (InRange(ev->mouse.x, 900, 1000)){
						CurrentWorld->EnemySelect = true;
						SelectedEnemy = EnemyType::E_Dankey;
					}
					else if (InRange(ev->mouse.x, 1000, 1100)){
						CurrentWorld->EnemySelect = true;
						SelectedEnemy = EnemyType::E_Cinas;
					}
				}
				else if(CurrentWorld->bPlay) {
					TinTin->bShooting = true;
				}
				else {
					if (!CurrentWorld->bPlay) {
						bClicked = true;

						//check if user is changing start position
						if (ChangingStart) {
							ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
							CharacterStart = ClickLocation;
						}
						//check if enemy select is true
						else if (CurrentWorld->EnemySelect) {
							//get the mouse location
							ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));

							//get the tile that was clicked
							clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

							if (SelectedEnemy == EnemyType::E_Dankey && !clickedTile->occupied && !CurrentWorld->Blocks[(int)(clickedTile->location.x / CurrentWorld->gridSize)][(int)(clickedTile->location.y / CurrentWorld->gridSize)].bSpawned && !CurrentWorld->Blocks[(int)(clickedTile->location.x / CurrentWorld->gridSize)][(int)((clickedTile->location.y + 32) / CurrentWorld->gridSize)].bSpawned){
								CurrentWorld->PlaceEnemy(clickedTile, SelectedEnemy);
							}
							if (SelectedEnemy == EnemyType::E_Cinas && !clickedTile->occupied && !CurrentWorld->Blocks[(int)(clickedTile->location.x / CurrentWorld->gridSize)][(int)(clickedTile->location.y / CurrentWorld->gridSize)].bSpawned){
								CurrentWorld->PlaceEnemy(clickedTile, SelectedEnemy);
							}
						}
						//Check if the box placement mode isn't enabled
						else if (!bBoxSelect && !CurrentWorld->EnemySelect) {
							//Get the mouse's location
							ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));

							//Get the tile that was clicked
							clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

							if (!clickedTile->occupied){
								//Place a new block if there isn't already a block in that location
								CurrentWorld->PlaceBlock(clickedTile, SelectedBlock);
							}
						}
						else if (bBoxSelect && !CurrentWorld->EnemySelect) {
							//If a start location of the rectangle select has been set
							if (bFirstBoxSelected){
								Vector2D NewMouseLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1) + 64, GEngine->GetMouseState().y + (GridBuffer.offset.y * -1) + 32);
								Vector2D BoxVector;

								//Handle different directions in which the box extends
								if (NewMouseLocation > ClickLocation) {
									BoxVector = ClickLocation;
								}
								else{
									BoxVector = NewMouseLocation;
								}

								//Place multiple boxes
								for (int i = 0; i < abs((int)(NewMouseLocation.x - ClickLocation.x) / 32); i++) {
									for (int j = 0; j < abs((int)(NewMouseLocation.y - ClickLocation.y) / 32); j++) {
										CurrentWorld->PlaceBlock(CurrentWorld->GetClickedTile(BoxVector + Vector2D(i * 32, j * 32)), SelectedBlock);
									}
								}
							}

							bFirstBoxSelected = !bFirstBoxSelected;
							ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
							FirstTile = CurrentWorld->GetClickedTile(ClickLocation);
						}
					}
				}
				break;
			case MOUSE_RB:
				//Check if the box placement mode isn't enabled
				if (!bBoxSelect) {
					//Get the mouse's location
					ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));

					//Get the tile that was clicked
					clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

					//Destroy the block the target location
					if (clickedTile){
						CurrentWorld->DestroyBlock(clickedTile);
					}
				}
				else {
					//If a start location of the rectangle select has been set
					if (bFirstBoxSelected){
						Vector2D NewMouseLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
						Vector2D BoxVector;

						//Handle different directions in which the box extends
						if (NewMouseLocation > ClickLocation) {
							BoxVector = ClickLocation;
						}
						else{
							BoxVector = NewMouseLocation;
						}

						//Destroy a rectangle of boxes
						for (int i = 0; i < abs((int)(NewMouseLocation.x - ClickLocation.x) / 32); i++) {
							for (int j = 0; j < abs((int)(NewMouseLocation.y - ClickLocation.y) / 32); j++) {
								CurrentWorld->DestroyBlock(CurrentWorld->GetClickedTile(BoxVector + Vector2D(i * 32, j * 32)));
							}
						}
					}

					//Toggle whether the first point of the rectangle has been set
					bFirstBoxSelected = !bFirstBoxSelected;

					//Set the first selected Tile
					ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
					FirstTile = CurrentWorld->GetClickedTile(ClickLocation);
				}
				break;
			case MOUSE_MB:
				bMouseDrag = true;
				DragStart = Vector2D(ev->mouse.x, ev->mouse.y);
				break;
			}
		}
		//On MouseUp
		else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (CurrentWorld->bPlay){
				TinTin->bShooting = false;
			}
			bClicked = false;

			switch (ev->mouse.button) {
			case MOUSE_MB:
				bMouseDrag = false;
				DragVelocity = DragStart / DragTime;
				break;
			default:
				break;
			}
		}
	}
}

void PlayState::Tick(float delta){
	//If both are false, stop moving
	if ((!(al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_A) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_LEFT)) && !(al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_D) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_RIGHT))) && CurrentWorld->bPlay){
		//WorldMoveDelta.x = 0.f;
		TinTin->bRunning = false;
		TinTin->velocity.x = 0;
	}

	//Evaluate character directions
	if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_D) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_RIGHT) && CurrentWorld->bPlay)){
		if (!TinTin->bRunning || Priority == ECharacterDirection::R_Left) {
			Priority = ECharacterDirection::R_Left;
			TinTin->SetCharacterDirection(ECharacterDirection::R_Right);
			TinTin->bRunning = true;
		}
	}
	else if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_D) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_RIGHT) && !CurrentWorld->bPlay)){
		WorldMoveDelta.x = -5.f;
	}
	if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_A) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_LEFT) && CurrentWorld->bPlay)){
		if (!TinTin->bRunning || Priority == ECharacterDirection::R_Right) {
			Priority = ECharacterDirection::R_Right;
			TinTin->SetCharacterDirection(ECharacterDirection::R_Left);
			TinTin->bRunning = true;
		}
	}
	else if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_A) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_LEFT) && !CurrentWorld->bPlay)){
		WorldMoveDelta.x = 5.f;
	}

	if (Priority == ECharacterDirection::R_Right){
		if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_D) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_RIGHT) && CurrentWorld->bPlay)){
			TinTin->SetCharacterDirection(ECharacterDirection::R_Right);
		}
	}
	if (Priority == ECharacterDirection::R_Left){
		if ((al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_A) || al_key_down(&GEngine->GetKeyboardState(), ALLEGRO_KEY_LEFT) && CurrentWorld->bPlay)){
			TinTin->SetCharacterDirection(ECharacterDirection::R_Left);
		}
	}

	//Move character if bRunning is true
	if (TinTin->bRunning && TinTin->direction == ECharacterDirection::R_Right){
		TinTin->Run(Vector2D(1.f, 0.f));
	}
	else if (TinTin->bRunning && TinTin->direction == ECharacterDirection::R_Left){
		TinTin->Run(Vector2D(-1.f, 0.f));
	}
	//Character ticks
	for (int i = 0; i < (int) CurrCharacters.size(); i++ && CurrentWorld->bPlay) {
		CurrCharacters[i]->Tick(delta, &CurrCharacters);
	}

	if (InRange(GEngine->GetMouseState().x, PauseButton->position.x, PauseButton->position.x + PauseButton->width) && InRange(GEngine->GetMouseState().y, PauseButton->position.y, PauseButton->position.y + PauseButton->height)){
		PauseButton->onHoverIn();
	}
	else{
		PauseButton->onHoverOut();
	}
	if (!Paused) {
		if (CurrentWorld->bPlay) {

			//Run Gravity, Collision checking code, and Friction
			CurrentEffects->GravTick(CurrCharacters);
			ColChecker = CurrentEffects->ColTick(CurrentWorld, CurrCharacters);
			if (ColChecker == 1) {
				TinTin->Win(CharacterStart);
				CurrentWorld->bPlay = false;
			}
			if (ColChecker > 2){
				TypeChecker = dynamic_cast<Bullet*>(CurrCharacters[ColChecker - 2]);
				if (TypeChecker){
					CurrCharacters.push_back(new BulletEx(CurrCharacters[ColChecker - 2]->position, CurrCharacters[ColChecker - 2]->direction));
					DestroyCharacter(CurrCharacters[ColChecker - 2]);
				}
				else{
					DestroyCharacter(CurrCharacters[ColChecker - 2]);
				}
			}
			CurrentEffects->FricTick(CurrCharacters);

			//Kill the Character if he falls out of the world
			if (TinTin->position.x > CurrentWorld->dimensions.x || (TinTin->position.x + TinTin->ActualWidth) < 0 || TinTin->position.y > CurrentWorld->dimensions.y || (TinTin->position.y + TinTin->ActualHeight) < 0 || TinTin->Health <= 0) {
				CurrCharacters.clear();
				CurrCharacters.push_back(TinTin);
				TinTin->Die();
				TinTin->SetCharacterWorldPosition(CharacterStart);
				CurrentWorld->bPlay = false;
				TinTin->Health = 100.f;
			}
		}
		
		CurrentWorld->moveWorld(WorldMoveDelta, GridBuffer, Background, BlockBuffer, notPlayingBuff);
		
		//Run world tick
		CurrentWorld->Tick(delta);

		//Calculate the change in mouse position if the middle mouse button is being held
		Vector2D DragDelta;
		if (bMouseDrag){
			DragDelta = DragStart - Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
			CurrentWorld->moveWorld(DragDelta * -1, GridBuffer, Background, BlockBuffer, notPlayingBuff);
			DragStart = Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
			DragTime += delta;
		}

		PlayerOldPosition = TinTin->position;

		//Mouse states
		switch (GEngine->GetMouseState().buttons){
		case MOUSE_LB:
			if (!ChangingStart && !CurrentWorld->bPlay){
				if (!bBoxSelect && !CurrentWorld->EnemySelect){
					ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
					//Get the tile that was clicked
					clickedTile = CurrentWorld->GetClickedTile(ClickLocation);
					if (clickedTile) {
						CurrentWorld->PlaceBlock(clickedTile, SelectedBlock);
					}
				}
			}
			break;
		case MOUSE_MB:
			break;
		case MOUSE_RB:
			if (!bBoxSelect){
				ClickLocation = Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1), GEngine->GetMouseState().y + (GridBuffer.offset.y * -1));
				//Get the tile that was clicked
				clickedTile = CurrentWorld->GetClickedTile(ClickLocation);
				if (clickedTile){
					CurrentWorld->DestroyBlock(clickedTile);
				}
			}
		default:
			break;
		}
	}
}

void PlayState::Draw(){
	al_set_target_bitmap(UI.image);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_filled_rectangle(0, 0, GEngine->GetDisplayWidth(), 100, BLUE500);
	for (int i = 0; i < (int)SelectBlock.size(); i++){
		al_draw_bitmap(SelectBlock[i].image, SelectBlock[i].offset.x, SelectBlock[i].offset.y, ALLEGRO_VIDEO_BITMAP);
	}

	if (!CurrentWorld->bPlay){
		al_set_target_bitmap(notPlayingBuff.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	}
	else{
		//If the play mode has been selected, then draw the character
		al_set_target_bitmap(BlockBuffer.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	}
	//For-each loop that goes through every block in the array
	for (auto& sub : CurrentWorld->Blocks){
		for (auto& elem : sub){
			//Calculates the block's offset relative to the top left corner of the display
			elem.offset = elem.position + CurrentWorld->offset;

			//If the block has been created, draw it!
			if (elem.bSpawned && InRange(elem.offset.x, -32, al_get_display_width(GEngine->GetDisplay()) + 32) && InRange(elem.offset.y, -32, al_get_display_height(GEngine->GetDisplay()) + 32)){
				//Draws the block using a texture from the current selected type of block
				elem.Draw(CurrentWorld->Type[static_cast<int>(elem.type)].texture);
			}
		}
	}

	//draws characters if not playing
	if (CurrentWorld->bPlay) {
		for (int i = 0; i < (int)CurrCharacters.size(); i++) {
			CurrCharacters[i]->Draw();
		}
	}
	
	//Draws a transparent blue rectangle over the area selected by the box select
	if (bBoxSelect && bFirstBoxSelected) {
		GridTile* newTile = CurrentWorld->GetClickedTile(Vector2D(GEngine->GetMouseState().x + (GridBuffer.offset.x * -1) + 32, GEngine->GetMouseState().y + (GridBuffer.offset.y * -1) + 32));
		al_draw_filled_rectangle(FirstTile->location.x, FirstTile->location.y, newTile->location.x, newTile->location.y, al_map_rgba(6, 27, 73, 25));
	}

	//Draws Health bar
	if (CurrentWorld->bPlay){
		if (TinTin->Health >= 50){
			HealthBarColour = al_map_rgb(118, 255, 3);
		}
		else if (TinTin->Health < 50 && TinTin->Health >= 15){
			HealthBarColour = al_map_rgb(255, 255, 0);
		}
		else if (TinTin->Health < 15){
			HealthBarColour = al_map_rgb(213, 0, 0);
		}
		al_set_target_bitmap(HealthBar);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_draw_filled_rectangle(0, 0, (int)TinTin->Health, 32, HealthBarColour);
		al_draw_textf(GEngine->GetDebugFont(), al_map_rgb(0, 0, 0), (int)TinTin->Health + 1, 10, 0, "%.1f / 100.0", TinTin->Health);
	}

	//Reset the target bitmap to the backbuffer
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	//Draw the background image
	al_draw_bitmap_region(Background.image, Background.offset.x * -1, Background.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);



	//Draw the grid overlay if editor mode is enabled
	if (!CurrentWorld->bPlay) {
		al_draw_bitmap_region(GridBuffer.image, GridBuffer.offset.x * -1, GridBuffer.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
		if (!CurrentWorld->bPlay){
			al_set_target_bitmap(notPlayingBuff.image);
			for (int i = 0; i < (int)CurrentWorld->EnemiesStored.size(); i++) {
				if (CurrentWorld->EnemiesStored[i].Type == EnemyType::E_Dankey)
					al_draw_bitmap(DankeyTemp, CurrentWorld->EnemiesStored[i].position.x, CurrentWorld->EnemiesStored[i].position.y, 0);
				else if (CurrentWorld->EnemiesStored[i].Type == EnemyType::E_Cinas)
					al_draw_bitmap(CinasTemp, CurrentWorld->EnemiesStored[i].position.x, CurrentWorld->EnemiesStored[i].position.y, 0);
			}
			al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
		}
		al_draw_bitmap_region(notPlayingBuff.image, notPlayingBuff.offset.x * -1, notPlayingBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
		//Draw Enemy Previews if not playing
	}
	else {
		al_draw_bitmap_region(BlockBuffer.image, BlockBuffer.offset.x *-1, BlockBuffer.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
	}

	if (!CurrentWorld->bPlay){
		al_draw_bitmap(UI.image, 0, 0, 0);
	}
	if (CurrentWorld->bPlay){
		al_draw_bitmap(HealthBar, 0, al_get_display_height(GEngine->GetDisplay()) - 42, 0);
	}
}

void PlayState::Init(){
	//Set the different types of blocks, as well as load their textures
	CurrentWorld->Type[0] = BlockType("Rainbow", al_load_bitmap("Textures/Objects/Rainbow.png"), true);
	CurrentWorld->Type[1] = BlockType("Brick", al_load_bitmap("Textures/Objects/Brick.png"), true);
	CurrentWorld->Type[2] = BlockType("Grass", al_load_bitmap("Textures/Objects/Grass.png"), true);
	CurrentWorld->Type[3] = BlockType("Dirt", al_load_bitmap("Textures/Objects/Dirt.png"), true);
	CurrentWorld->Type[4] = BlockType("Stone", al_load_bitmap("Textures/Objects/Stone.png"), true);
	CurrentWorld->Type[5] = BlockType("Fancy", al_load_bitmap("Textures/Objects/Fancy.png"), true);
	CurrentWorld->Type[6] = BlockType("Mossy", al_load_bitmap("Textures/Objects/Mossy.png"), true);
	CurrentWorld->Type[7] = BlockType("Background Brick", al_load_bitmap("Textures/Objects/Background_Brick.png"), false);
	CurrentWorld->Type[8] = BlockType("Finish Flag", al_load_bitmap("Textures/Objects/FinishFlag.png"), false);

	for (int i = 0; i < 9; i++) {
		SelectBlock.push_back(Buffer(al_create_bitmap(100, 100), Vector2D(100.f * i, 0.f), Vector2D(0.f, 0.f)));
		al_set_target_bitmap(SelectBlock[i].image);
		al_clear_to_color(BLUE500);
		al_draw_bitmap(CurrentWorld->Type[i].texture, 34, 8, 0);
		al_draw_textf(GEngine->GetDebugFont(), WHITE, 50, 80, ALLEGRO_ALIGN_CENTER, "%s", CurrentWorld->Type[i].name);
	}
	SelectBlock.push_back(Buffer(al_create_bitmap(100, 100), Vector2D(900.f, 0.f), Vector2D(0.f, 0.f)));
	al_set_target_bitmap(SelectBlock[9].image);
	al_clear_to_color(BLUE500);
	al_draw_bitmap_region(al_load_bitmap("Textures/Characters/Dankeyidle_e.png"), 0, 0, 64, 64, 18, 8, 0);
	al_draw_textf(GEngine->GetDebugFont(), WHITE, 50, 80, ALLEGRO_ALIGN_CENTER, "%s", "Dankey");

	SelectBlock.push_back(Buffer(al_create_bitmap(100, 100), Vector2D(1000.f, 0.f), Vector2D(0.f, 0.f)));
	al_set_target_bitmap(SelectBlock[10].image);
	al_clear_to_color(BLUE500);
	al_draw_bitmap_region(al_load_bitmap("Textures/Characters/Cinasidle_e.png"), 0, 0, 32, 32, 18, 8, 0);
	al_draw_textf(GEngine->GetDebugFont(), WHITE, 34, 80, ALLEGRO_ALIGN_CENTER, "%s", "Cinas");

	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	//Create buffers used for rendering
	GridBuffer.image = al_create_bitmap(4096, 2048);
	notPlayingBuff.image = al_create_bitmap(4096, 2048);
	Background.image = al_create_bitmap(4096, 2048);
	BlockBuffer.image = al_create_bitmap(4096, 2048);
	UI.image = al_create_bitmap(GEngine->GetDisplayWidth(), 100);
	HealthBar = al_create_bitmap(500, 32);
	DankeyTemp = al_load_bitmap("Textures/Characters/DankeyTemp.png");
	CinasTemp = al_load_bitmap("Textures/Characters/CinasTemp.png");

	CurrCharacters.push_back(TinTin);	//registering main character in Character vector
	TinTin->velocity = Vector2D(0.f, 0.f);		//velocity starts at zero
	CharacterStart = Vector2D(0.f, 0.f);		//original character start position is zero
	ChangingStart = false;				//at beginning, start position is not being changed
	ColChecker = 0;

	//Setting Multiple Images to Background Buffer
	al_set_target_bitmap(Background.image);

	//Load the background image
	for (int i = 0; i < 2; i++) {
		for (int y = 0; y < 3; y++) {
			ALLEGRO_BITMAP* BackgroundTexture = al_load_bitmap("Textures/Scenes/Background_Gauss.png");
			if (BackgroundTexture) {
				al_draw_bitmap(BackgroundTexture, (y * 1024), (i * 1024), 0);
			}
			else {
				fprintf(stderr, "Could not load background image\n");
				GEngine->Quit();
			}
		}
	}

	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
	//Sets the draw target to the grid bitmap

	al_set_target_bitmap(GridBuffer.image);

	for (int i = 0; i < 129; i++){
		al_draw_line(i * CurrentWorld->gridSize, 0, i * CurrentWorld->gridSize, 2048, al_map_rgba(50, 50, 50, 150), 1);
	}
	for (int i = 0; i < 65; i++){
		al_draw_line(0, i * CurrentWorld->gridSize, 4096, i * CurrentWorld->gridSize, al_map_rgba(50, 50, 50, 150), 1);
	}
	//Sets the target bitmap back to the default buffer
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	if (GEngine->SharedVar.bLoadingLevel){
		CurrentWorld->Load(GEngine->SharedVar.LoadLevelName, &CurrCharacters);
	}
}

void PlayState::Pause(){
	Paused = true;
}

void PlayState::Resume(){
	Paused = false;
}

void PlayState::Destroy(){
	fflush(stdin);

	printf("Save level? (y/n): ");
	char cSave;
	scanf("%c", &cSave);
	fflush(stdin);
	if (tolower(cSave) == 'y'){
		char levelName[64];
		printf("Enter a file name: ");
		scanf("%s", levelName);
		if (CurrentWorld->Save(levelName, CurrCharacters)){
			printf("Saved level as %s\n", levelName);
			Online::PostLevel(levelName);
		}
		else{
			printf("Could not save level as %s\n", levelName);
		}
	}

	delete TinTin;
	al_destroy_bitmap(DankeyTemp);
	al_destroy_bitmap(CinasTemp);
	al_destroy_bitmap(BlockBuffer.image);
	al_destroy_bitmap(GridBuffer.image);
	al_destroy_mouse_cursor(CircleSelect);
}

PlayState::~PlayState(){
	delete CurrentEffects;
	delete CurrentWorld;
	delete PauseButton;

	//Delete all CurrCharacters from memory and clear the vector
	for (int i = 0; i < (int)CurrCharacters.size(); i++){
		delete CurrCharacters[i];
	}
	CurrCharacters.clear();
}

void PauseButtonDown(){
	GEngine->GetCurrentGameState()->Pause();
}