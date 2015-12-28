#include "PlayState.h"
#include "MainMenuState.h"

PlayState::PlayState(){
	CurrentWorld = new World(Vector2D(4096.f, 2048.f), 32);
	TinTin = new Player(128, 64);	//The main player character
	TinTin->SetCharacterWorldPosition(Vector2D(0.f, 0.f));
	CurrentEffects = new Effects(Vector2D(0.f, 1.f));		//current world gravity
	notPlayingBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f)); //block buffer for when not playing
	blockBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//play buffer for blocks
	dubBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//buffer for grid
	Background = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(2.5f, 2.5f));	//buffer for background
	CurrentWorld->bPlay = false;
	BoxSelectCursor = al_load_bitmap("Textures/Cursor_BoxSelect.png");
	CircleSelect = al_create_mouse_cursor(BoxSelectCursor, 8, 8);

	PauseButton = new Button(al_map_rgb(255, 255, 255), BLUE500, 32, 32, Vector2D(0.f, 0.f), 2, "||", &PauseButtonDown);
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
				//Close window if escape key is pressed
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				if (CurrentWorld->bPlay)
					TinTin->SetCharacterDirection(ECharacterDirection::R_Right);
				TinTin->Run(Vector2D(5.f, 0.f));
				WorldMoveDelta.x = -5.f;
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				if (CurrentWorld->bPlay)
					TinTin->SetCharacterDirection(ECharacterDirection::R_Left);
				TinTin->Run(Vector2D(-5.f, 0.f));
				WorldMoveDelta.x = 5.f;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				WorldMoveDelta.y = -5.f;
				break;
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				TinTin->Jump();
				WorldMoveDelta.y = 5.f;
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
			case ALLEGRO_KEY_1:
				if (!CurrentWorld->EnemySelect)
					SelectedBlock = EBlockType::B_Rainbow;
				else if (CurrentWorld->EnemySelect)
					SelectedEnemy = EnemyType::E_Cinas;
				break;
			case ALLEGRO_KEY_2:
				if (!CurrentWorld->EnemySelect)
					SelectedBlock = EBlockType::B_Brick;
				else if (CurrentWorld->EnemySelect)
					SelectedEnemy = EnemyType::E_Dankey;
				break;
			case ALLEGRO_KEY_3:
				if (!CurrentWorld->EnemySelect)
					SelectedBlock = EBlockType::B_Grass;
				else if (CurrentWorld->EnemySelect)
					SelectedEnemy = EnemyType::E_Yash;
				break;
			case ALLEGRO_KEY_4:
				SelectedBlock = EBlockType::B_Dirt;
				break;
			case ALLEGRO_KEY_5:
				SelectedBlock = EBlockType::B_Stone;
				break;
			case ALLEGRO_KEY_6:
				SelectedBlock = EBlockType::B_Fancy;
				break;
			case ALLEGRO_KEY_7:
				SelectedBlock = EBlockType::B_Mossy;
				break;
			case ALLEGRO_KEY_SPACE:
				if (!CurrentWorld->bPlay){
					CurrentWorld->bPlay = true;
				}
				else {
					CurrentWorld->bPlay = false;
					TinTin->SetCharacterWorldPosition(Vector2D(0.f, 0.f));
				}
				CurrentEffects->GonOff[TinTin->gravSlot] = true;
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
			default:
				break;
			}
		}
		//On KeyUp
		else if (ev->type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev->keyboard.keycode) {
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				WorldMoveDelta.x = 0.f;
				TinTin->bRunning = false;
				TinTin->velocity.x = 0;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				WorldMoveDelta.y = 0.f;
				break;
			case ALLEGRO_KEY_M:
				GEngine->ChangeGameState<MainMenuState>();
				break;
			default:
				break;
			}
		}

		//On mouse click
		else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			switch (ev->mouse.button){
			case MOUSE_LB:
				if (!CurrentWorld->bPlay) {
					bClicked = true;

					//check if enemy select is true
					if (CurrentWorld->EnemySelect){
							//get the mouse location
							ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));

							//get the tile that was clicked
							clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

							if (!clickedTile->occupied){
								CurrentWorld->PlaceEnemy(clickedTile, SelectedEnemy, &AllDankeys);
							}
					}
					//Check if the box placement mode isn't enabled
					else if (!bBoxSelect) {
						//Get the mouse's location
						ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));

						//Get the tile that was clicked
						clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

						if (!clickedTile->occupied){
							//Place a new block if there isn't already a block in that location
							CurrentWorld->PlaceBlock(clickedTile, SelectedBlock);
						}
					}
					else if (bBoxSelect) {
						//If a start location of the rectangle select has been set
						if (bFirstBoxSelected){
							Vector2D NewMouseLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
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
						ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
						FirstTile = CurrentWorld->GetClickedTile(ClickLocation);
					}
				}
				break;
			case MOUSE_RB:
				//Check if the box placement mode isn't enabled
				if (!bBoxSelect) {
					//Get the mouse's location
					ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));

					//Get the tile that was clicked
					clickedTile = CurrentWorld->GetClickedTile(ClickLocation);

					//Destroy the block the target location
					CurrentWorld->DestroyBlock(clickedTile);
				}
				else {
					//If a start location of the rectangle select has been set
					if (bFirstBoxSelected){
						Vector2D NewMouseLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
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
					ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
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
	if (InRange(GEngine->GetMouseState().x, PauseButton->position.x, PauseButton->position.x + PauseButton->width) && InRange(GEngine->GetMouseState().y, PauseButton->position.y, PauseButton->position.y + PauseButton->height)){
		PauseButton->onHoverIn();
	}
	else{
		PauseButton->onHoverOut();
	}
	if (!Paused) {
		if (CurrentWorld->bPlay) {
			CurrentEffects->GravTick();
			CurrentEffects->ColTick(CurrentWorld, *TinTin);
		}
		if (TinTin->GetCharacterWorldPosition().y < CurrentWorld->dimensions.x){
			TinTin->Die();
		}
		if (!TinTin->bOnGround && CurrentWorld->Blocks[(int)((TinTin->GetCharacterWorldPosition().x + 32) / CurrentWorld->gridSize)][(int)(TinTin->GetCharacterWorldPosition().y + TinTin->ActualHeight) / CurrentWorld->gridSize].bSpawned) {
			TinTin->SetCharacterWorldPosition(Vector2D(TinTin->GetCharacterWorldPosition().x, CurrentWorld->Blocks[(int)((TinTin->GetCharacterWorldPosition().x) / CurrentWorld->gridSize)][(int)(TinTin->GetCharacterWorldPosition().y) / CurrentWorld->gridSize].position.y));
			TinTin->bOnGround = true;
			if (TinTin->velocity.y > 0) {
				TinTin->velocity.y = 0;
			}
			CurrentEffects->GonOff[TinTin->gravSlot] = false;
		}
		else if (!CurrentWorld->Blocks[(int)((TinTin->GetCharacterWorldPosition().x + 32) / CurrentWorld->gridSize)][(int)(TinTin->GetCharacterWorldPosition().y + TinTin->ActualHeight) / CurrentWorld->gridSize].bSpawned) {
			TinTin->bOnGround = false;
			CurrentEffects->GonOff[TinTin->gravSlot] = true;
		}

		TinTin->Tick(delta);
		CurrentWorld->Tick(delta);
		CurrentWorld->moveWorld(WorldMoveDelta, dubBuff, Background, blockBuff, notPlayingBuff, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()));

		Vector2D DragDelta;
		if (bMouseDrag){
			DragDelta = DragStart - Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
			CurrentWorld->moveWorld(DragDelta * -1, dubBuff, Background, blockBuff, notPlayingBuff, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()));
			DragStart = Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
			DragTime += delta;
		}

		switch (GEngine->GetMouseState().buttons){
		case MOUSE_LB:
			if (!bBoxSelect){
				ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
				//Get the tile that was clicked
				clickedTile = CurrentWorld->GetClickedTile(ClickLocation);
				CurrentWorld->PlaceBlock(clickedTile, SelectedBlock);
			}
			break;
		case MOUSE_MB:
			break;
		case MOUSE_RB:
			if (!bBoxSelect){
				ClickLocation = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
				//Get the tile that was clicked
				clickedTile = CurrentWorld->GetClickedTile(ClickLocation);
				CurrentWorld->DestroyBlock(clickedTile);
			}
		default:
			break;
		}
	}
}

void PlayState::Draw(){
	if (!CurrentWorld->bPlay){
		al_set_target_bitmap(notPlayingBuff.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	}
	else{
		//If the play mode has been selected, then draw the character
		al_set_target_bitmap(blockBuff.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		TinTin->Draw();
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

	//Draws a transparent blue rectangle over the area selected by the box select
	if (bBoxSelect && bFirstBoxSelected) {
		GridTile* newTile = CurrentWorld->GetClickedTile(Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1)));
		al_draw_filled_rectangle(FirstTile->location.x, FirstTile->location.y, newTile->location.x, newTile->location.y, al_map_rgba(6, 27, 73, 25));
	}

	//Reset the target bitmap to the backbuffer
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	//Draw the background image
	al_draw_bitmap_region(Background.image, Background.offset.x * -1, Background.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);

	//Draw the grid overlay if editor mode is enabled
	if (!CurrentWorld->bPlay) {
		al_draw_bitmap_region(dubBuff.image, dubBuff.offset.x * -1, dubBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
		al_draw_bitmap_region(notPlayingBuff.image, notPlayingBuff.offset.x * -1, notPlayingBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
	}
	else {
		al_draw_bitmap_region(blockBuff.image, blockBuff.offset.x *-1, blockBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
	}
	
	//Draw the pause button
	PauseButton->Draw();
}

void PlayState::Init(){
	//Set the different types of blocks, as well as load their textures
	CurrentWorld->Type[0] = BlockType("Rainbow", al_load_bitmap("Textures/Objects/Rainbow.png"));
	CurrentWorld->Type[1] = BlockType("Brick", al_load_bitmap("Textures/Objects/Brick.png"));
	CurrentWorld->Type[2] = BlockType("Grass", al_load_bitmap("Textures/Objects/Grass.png"));
	CurrentWorld->Type[3] = BlockType("Dirt", al_load_bitmap("Textures/Objects/Dirt.png"));
	CurrentWorld->Type[4] = BlockType("Stone", al_load_bitmap("Textures/Objects/Stone.png"));
	CurrentWorld->Type[5] = BlockType("Fancy", al_load_bitmap("Textures/Objects/Fancy.png"));
	CurrentWorld->Type[6] = BlockType("Mossy", al_load_bitmap("Textures/Objects/Mossy.png"));

	//Create buffers used for rendering
	dubBuff.image = al_create_bitmap(4096, 2048);
	notPlayingBuff.image = al_create_bitmap(4096, 2048);
	Background.image = al_create_bitmap(4096, 2048);
	blockBuff.image = al_create_bitmap(4096, 2048);

	TinTin->gravSlot = CurrentEffects->Register(TinTin, TinTinGrav);	//registering main character in gravity queue (is affected at beginning)
	TinTin->velocity = Vector2D(0.f, 0.f);		//velocity starts at zero

	//Setting Multiple Images to Background Buffer
	al_set_target_bitmap(Background.image);

	//Load the background image
	for (int i = 0; i < 2; i++) {
		for (int y = 0; y < 3; y++) {
			al_draw_bitmap(al_load_bitmap("Textures/Scenes/Background_Original.png"), (y * 1024), (i * 1024), 0);
		}
	}

	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
	//Sets the draw target to the grid bitmap

	al_set_target_bitmap(dubBuff.image);

	for (int i = 0; i < 129; i++){
		al_draw_line(i * CurrentWorld->gridSize, 0, i * CurrentWorld->gridSize, 2048, al_map_rgba(50, 50, 50, 150), 1);
	}
	for (int i = 0; i < 65; i++){
		al_draw_line(0, i * CurrentWorld->gridSize, 4096, i * CurrentWorld->gridSize, al_map_rgba(50, 50, 50, 150), 1);
	}
	//Sets the target bitmap back to the default buffer
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	printf("Read saved level? (y/n): ");
	char cRead;
	scanf("%c", &cRead);
	if (tolower(cRead) == 'y'){
		fflush(stdin);
		char loadLevel[64];
		printf("Enter level name: ");
		scanf("%s", loadLevel);
		fflush(stdin);
		strcat(loadLevel, ".bvl");
		if (CurrentWorld->Load(loadLevel)){
			printf("Loaded %s\n", loadLevel);
		}
		else{
			printf("Could not load %s\n", loadLevel);
		}
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
		strcat(levelName, ".bvl");

		if (CurrentWorld->Save(levelName)){

			printf("Saved level as %s\n", levelName);
		}
		else{
			printf("Could not save level as %s\n", levelName);
		}
	}

	delete TinTin;
	al_destroy_bitmap(blockBuff.image);
	al_destroy_bitmap(dubBuff.image);
	al_destroy_mouse_cursor(CircleSelect);
}

PlayState::~PlayState(){
	delete CurrentEffects;
	delete CurrentWorld;
}

void PauseButtonDown(){
	GEngine->GetCurrentGameState()->Pause();
}