#include "PlayState.h"
#include "MainMenuState.h"

PlayState::PlayState(){
	CurrentWorld = new World(Vector2D(4096.f, 2048.f), 32);
	TinTin = Character(Vector2D(0, 0), 64, 128);	//TinTin character
	CurrentGrav = new Gravity(Vector2D(0.f, 5.f));		//current world gravity
	notPlayingBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f)); //block buffer for when not playing
	blockBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//play buffer for blocks
	dubBuff = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(5.f, 5.f));	//buffer for grid
	Background = Buffer(NULL, Vector2D(0.f, 0.f), Vector2D(2.5f, 2.5f));	//buffer for background
	CurrentWorld->bPlay = false;
}

void PlayState::HandleEvents(ALLEGRO_EVENT *ev){
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev->keyboard.keycode) {
			//Close window if escape key is pressed
		case ALLEGRO_KEY_D:
		case ALLEGRO_KEY_RIGHT:
			TinTin.flipped = false;
			moveDelta.x = -5.f;
			TinTin.moving = true;
			break;
		case ALLEGRO_KEY_A:
		case ALLEGRO_KEY_LEFT:
			moveDelta.x = 5.f;
			TinTin.moving = true;
			TinTin.flipped = true;
			break;
		case ALLEGRO_KEY_S:
		case ALLEGRO_KEY_DOWN:
			moveDelta.y = -5.f;
			break;
		case ALLEGRO_KEY_W:
		case ALLEGRO_KEY_UP:
			moveDelta.y = 5.f;
			break;
		case ALLEGRO_KEY_C:
			bBoxSelect = !bBoxSelect;
			break;
		case ALLEGRO_KEY_1:
			SelectedBlock = EBlockType::B_Rainbow;
			break;
		case ALLEGRO_KEY_2:
			SelectedBlock = EBlockType::B_Brick;
			break;
		case ALLEGRO_KEY_3:
			SelectedBlock = EBlockType::B_Grass;
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
				//TinTin.position = Vector2D(0.f, 0.f);
			}
			CurrentGrav->GonOff[TinTin.gravSlot] = true;
		case ALLEGRO_KEY_BACKSPACE:
			if (!DeleteMode) {
				DeleteMode = true;
			}
			else {
				DeleteMode = false;
			}

		default:
			break;
		}
	}
	//On KeyUp
	else if (ev->type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev->keyboard.keycode) {
		case ALLEGRO_KEY_D:
		case ALLEGRO_KEY_RIGHT:
			TinTin.moving = false;
		case ALLEGRO_KEY_A:
		case ALLEGRO_KEY_LEFT:
			moveDelta.x = 0.f;
			TinTin.moving = false;
			break;
		case ALLEGRO_KEY_S:
		case ALLEGRO_KEY_DOWN:
		case ALLEGRO_KEY_W:
		case ALLEGRO_KEY_UP:
			moveDelta.y = 0.f;
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
				if (!bBoxSelect) {
					//Get the mouse's location
					Clicked = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));
					//Get the tile that was clicked
					clickedTile = CurrentWorld->getClickedTile(Clicked);

					if (!DeleteMode) {
						//if the tile is not already occupied by a block, create a new block
						if (!clickedTile.occupied){
							CurrentWorld->Blocks[clickedTile.x][clickedTile.y] = Block(clickedTile.location, SelectedBlock);
							CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = true;
							clickedTile.occupied = true;
						}
					}
					else if (DeleteMode) {
						CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = false;
						clickedTile.occupied = false;
					}

				}
				else{
					Clicked = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));

					FirstTile = CurrentWorld->getClickedTile(Clicked);
				}
			}
			break;
		case MOUSE_RB:
			bMouseDrag = true;
			DragStart = Vector2D(ev->mouse.x, ev->mouse.y);
			break;
		case MOUSE_MB:
			printf("mmb pressed\n");
			break;
		}
	}
	//On MouseUp
	else if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

		bClicked = false;

		if (ev->mouse.button == MOUSE_RB){
			bMouseDrag = false;
			DragVelocity = DragStart / DragTime;
		}
	}
}

void PlayState::Tick(){

	/*TinTin.EvHandle();
	TinTin.DoEv('f');
	if (CurrentWorld->Blocks[(int)(TinTin.position.x / CurrentWorld->gridSize)][(int)(TinTin.position.y + TinTin.ActualHeight) / CurrentWorld->gridSize].bSpawned) {
		CurrentGrav->GonOff[TinTin.gravSlot] = false;
		al_destroy_bitmap(TinTin.spritesheet);
		TinTin.DoEv('i');
	}
	else if (!CurrentWorld->Blocks[(int)(TinTin.position.x / CurrentWorld->gridSize)][(int)(TinTin.position.y + TinTin.ActualHeight) / CurrentWorld->gridSize].bSpawned) {
		CurrentGrav->GonOff[TinTin.gravSlot] = true;
	}
	if (CurrentGrav->GonOff[TinTin.gravSlot] && TinTin.spritesheet) {
		al_destroy_bitmap(TinTin.spritesheet);
		TinTin.DoEv('f');
	}
	if (TinTin.moving && TinTin.animation == 'f') {
		if (!TinTin.flipped)
			TinTin.position.x += TinTin.delta.x;
		else
			TinTin.position.x -= TinTin.delta.x;
	}
	else if (TinTin.moving) {
		al_destroy_bitmap(TinTin.spritesheet);
		TinTin.DoEv('r');
		if (!TinTin.flipped)
			TinTin.position.x += TinTin.delta.x;
		else
			TinTin.position.x -= TinTin.delta.x;
	}
	if (CurrentWorld->bPlay) {
		CurrentGrav->Tick();
	}*/
	
	CurrentWorld->Tick(delta);
	CurrentWorld->moveWorld(moveDelta, dubBuff, Background, blockBuff, notPlayingBuff, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()));

	if (bMouseDrag){
		Vector2D DragDelta = DragStart - Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
		CurrentWorld->moveWorld(DragDelta * -1, dubBuff, Background, blockBuff, notPlayingBuff, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()));
		DragStart = Vector2D(GEngine->GetMouseState().x, GEngine->GetMouseState().y);
		DragTime += delta;
	}

	if (bClicked && !bBoxSelect){
		Clicked = Vector2D(GEngine->GetMouseState().x + (dubBuff.offset.x * -1), GEngine->GetMouseState().y + (dubBuff.offset.y * -1));

		//Get the tile that was clicked
		clickedTile = CurrentWorld->getClickedTile(Clicked);
		if (!DeleteMode) {
			//if the tile is not already occupied by a block, create a new block
			if (!clickedTile.occupied){
				CurrentWorld->Blocks[clickedTile.x][clickedTile.y] = Block(clickedTile.location, SelectedBlock);
				CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = true;
				clickedTile.occupied = true;
			}
		}
		else if (DeleteMode) {
			CurrentWorld->Blocks[clickedTile.x][clickedTile.y].bSpawned = false;
			clickedTile.occupied = false;
		}
	}
}

void PlayState::Draw(){
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);

	if (!CurrentWorld->bPlay){
		al_set_target_bitmap(notPlayingBuff.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	}
	else{
		al_set_target_bitmap(blockBuff.image);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		//TinTin.Animate(TinTin.flipped);
	}
	//Foreach loop that goes through every block

	al_hold_bitmap_drawing(true);
	for (auto& sub : CurrentWorld->Blocks){
		for (auto& elem : sub){
			//If the block has been created, draw it!
			elem.offset = elem.position + CurrentWorld->offset;

			if (elem.bSpawned && InRange(elem.offset.x, -32, al_get_display_width(GEngine->GetDisplay()) + 32) && InRange(elem.offset.y, -32, al_get_display_height(GEngine->GetDisplay()) + 32)){
				elem.Draw(CurrentWorld->Type[static_cast<int>(elem.type)].texture);
			}
		}
	}

	al_hold_bitmap_drawing(false);

	if (bBoxSelect) {
		GridTile newTile = CurrentWorld->getClickedTile(Vector2D(state.x + (dubBuff.offset.x * -1), state.y + (dubBuff.offset.y * -1)));
		al_draw_filled_rectangle(FirstTile.location.x, FirstTile.location.y, newTile.location.x, newTile.location.y, al_map_rgba(137, 231, 255, 100));
	}

	//Draws TinTin character (idle, east)
	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));

	al_draw_bitmap_region(Background.image, Background.offset.x * -1, Background.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);


	if (!CurrentWorld->bPlay) {
		al_draw_bitmap_region(dubBuff.image, dubBuff.offset.x * -1, dubBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
		al_draw_bitmap_region(notPlayingBuff.image, notPlayingBuff.offset.x * -1, notPlayingBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
	}
	else {
		al_draw_bitmap_region(blockBuff.image, blockBuff.offset.x *-1, blockBuff.offset.y * -1, al_get_display_width(GEngine->GetDisplay()), al_get_display_height(GEngine->GetDisplay()), 0, 0, 0);
	}

	al_set_target_bitmap(al_get_backbuffer(GEngine->GetDisplay()));
}

void PlayState::Init(){
	CurrentWorld->Type[0] = BlockType("Rainbow", al_load_bitmap("Textures/Rainbow.png"));
	CurrentWorld->Type[1] = BlockType("Brick", al_load_bitmap("Textures/Brick.png"));
	CurrentWorld->Type[2] = BlockType("Grass", al_load_bitmap("Textures/Grass.png"));
	CurrentWorld->Type[3] = BlockType("Dirt", al_load_bitmap("Textures/Dirt.png"));
	CurrentWorld->Type[4] = BlockType("Stone", al_load_bitmap("Textures/Stone.png"));
	CurrentWorld->Type[5] = BlockType("Fancy", al_load_bitmap("Textures/Fancy.png"));
	CurrentWorld->Type[6] = BlockType("Mossy", al_load_bitmap("Textures/Mossy.png"));

	dubBuff.image = al_create_bitmap(4096, 2048);
	notPlayingBuff.image = al_create_bitmap(4096, 2048);
	Background.image = al_create_bitmap(4096, 2048);
	blockBuff.image = al_create_bitmap(4096, 2048);

	//TinTin.gravSlot = CurrentGrav->Register(&TinTin, TinTinGrav);	//registering main character in gravity queue (is affected at beginning)


	//Setting Multiple Images to Background Buffer
	al_set_target_bitmap(Background.image);

	for (int i = 0; i < 2; i++) {
		for (int y = 0; y < 3; y++) {
			al_draw_bitmap(al_load_bitmap("Textures/Background_Original.png"), (y * 1024), (i * 1024), 0);
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

}

void PlayState::Resume(){

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
}

PlayState::~PlayState(){
	delete CurrentGrav;
	delete CurrentWorld;
}