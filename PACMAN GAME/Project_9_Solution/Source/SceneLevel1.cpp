#include "SceneLevel1.h"

#include "ModuleInput.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"



SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	int scene = 1;

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_level_0.png");
	extraTexture = App->textures->Load("Assets/Sprites/Extras_background.png");

	speedx = 5;
	speedy = 5;

	speed_num_x = 3;
	speed_num_y = 3;

	//Music
	round = App->audio->LoadFx("Assets/Music/FX/opening-fanfare.wav");
	App->audio->PlayFx(round);
	App->audio->PlayMusic("Assets/Music/Music/Toy Box World (World 0).ogg", 25.0f);

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789." };
	scoreFont2 = App->fonts->Load("Assets/Fonts/Letters_Groups2.png", lookupTable2, 1);

	//PRINT COLIDERS PAREDES
	for (int j = 0; j <= 28; ++j)
	{
		for (int i = 0; i <= 37; ++i)
		{
			LOG("En %d,%d hay un %d", i, j, TileSet[i][j])
		}
	}

	//SuperPacdots ---
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 22, 64);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 204 , 64);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 29, 248);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 197, 248);


	//Pacdots --- IZQUIERDA
	App->particles->AddPacdot(App->particles->PacdotAnim, 114, 57);

	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 57);
	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 90, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 66, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 54, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 42, 42);

	App->particles->AddPacdot(App->particles->PacdotAnim, 30, 42);

	App->particles->AddPacdot(App->particles->PacdotAnim, 32, 57);

	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 57);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 69);

	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 25, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 53, 82);

	App->particles->AddPacdot(App->particles->PacdotAnim, 53, 67);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 67);
	
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 67);
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 80);
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 93);

	App->particles->AddPacdot(App->particles->PacdotAnim, 51, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 106);

	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 120);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 134);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 147);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 173);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 186);

	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 50, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 63, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 76, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 89, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 186);

	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 199);
	
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 90, 210);
	
	App->particles->AddPacdot(App->particles->PacdotAnim, 51, 226);
	App->particles->AddPacdot(App->particles->PacdotAnim, 64, 226);
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 226);

	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 25, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 38, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 51, 210);

	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 234);

	App->particles->AddPacdot(App->particles->PacdotAnim, 23, 234);
	App->particles->AddPacdot(App->particles->PacdotAnim, 34, 234);

	App->particles->AddPacdot(App->particles->PacdotAnim, 38, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 51, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 64, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 90, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 249);

	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 223);
	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 236);
	
	//Pacdots --- DERECHA
	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 57);

	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 138, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 150, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 162, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 42);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 42);

	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 42);

	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 57);

	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 57);
	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 69);

	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 203, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 175, 82);
	
	App->particles->AddPacdot(App->particles->PacdotAnim, 175, 67);
	App->particles->AddPacdot(App->particles->PacdotAnim, 163, 67);

	App->particles->AddPacdot(App->particles->PacdotAnim, 150, 67);
	App->particles->AddPacdot(App->particles->PacdotAnim, 150, 80);
	App->particles->AddPacdot(App->particles->PacdotAnim, 150, 93);

	App->particles->AddPacdot(App->particles->PacdotAnim, 177, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 163, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 150, 106);

	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 120);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 134);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 147);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 173);
	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 186);

	App->particles->AddPacdot(App->particles->PacdotAnim, 191, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 178, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 165, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 152, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 139, 186);
	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 186);

	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 199);

	App->particles->AddPacdot(App->particles->PacdotAnim, 151, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 138, 210);

	App->particles->AddPacdot(App->particles->PacdotAnim, 177, 226);
	App->particles->AddPacdot(App->particles->PacdotAnim, 164, 226);
	App->particles->AddPacdot(App->particles->PacdotAnim, 151, 226);

	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 203, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 190, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 177, 210);

	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 234);

	App->particles->AddPacdot(App->particles->PacdotAnim, 205, 234);
	App->particles->AddPacdot(App->particles->PacdotAnim, 194, 234);

	App->particles->AddPacdot(App->particles->PacdotAnim, 190, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 177, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 164, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 151, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 138, 249);
	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 249);

	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 223);
	App->particles->AddPacdot(App->particles->PacdotAnim, 126, 236);

	

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 115, 133);
	App->enemies->AddEnemy(Enemy_Type::INKY, 104, 136);
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 145, 133);
	App->enemies->AddEnemy(Enemy_Type::PINKY, 104, 120);
	
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->fonts->Enable();
	App->collisions->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	
	/*App->render->camera.x += 15;*/

	if (App->particles->COUNTDOWN <= 0)
	{
		LOG("VICTORY");
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
		App->fonts->BlitText(position_clear_x2 + 60, position_clear_y, scoreFont, "R");
		App->fonts->BlitText(position_clear_x2 + 75, position_clear_y, scoreFont, "O");
		App->fonts->BlitText(position_clear_x2 + 90, position_clear_y, scoreFont, "U");
		App->fonts->BlitText(position_clear_x2 + 105, position_clear_y, scoreFont, "N");
		App->fonts->BlitText(position_clear_x2 + 120, position_clear_y, scoreFont, "D");

		App->fonts->BlitText(position_clear_x + 0, position_clear_y, scoreFont, "C");
		App->fonts->BlitText(position_clear_x + 15, position_clear_y, scoreFont, "L");
		App->fonts->BlitText(position_clear_x + 30, position_clear_y, scoreFont, "E");
		App->fonts->BlitText(position_clear_x + 45, position_clear_y, scoreFont, "A");
		App->fonts->BlitText(position_clear_x + 60, position_clear_y, scoreFont, "R");
		App->fonts->BlitText(position_clear_x + 75, position_clear_y, scoreFont, "!");

		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();
		
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneGameOver, 30);
		App->audio->PlayMusic("Assets/Music/Ending.ogg");
		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();
	}

	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN)
	{
		LOG("VICTORY");
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
		App->fonts->BlitText(position_clear_x2 + 60, position_clear_y, scoreFont, "R");
		App->fonts->BlitText(position_clear_x2 + 75, position_clear_y, scoreFont, "O");
		App->fonts->BlitText(position_clear_x2 + 90, position_clear_y, scoreFont, "U");
		App->fonts->BlitText(position_clear_x2 + 105, position_clear_y, scoreFont, "N");
		App->fonts->BlitText(position_clear_x2 + 120, position_clear_y, scoreFont, "D");

		App->fonts->BlitText(position_clear_x + 0, position_clear_y, scoreFont, "C");
		App->fonts->BlitText(position_clear_x + 15, position_clear_y, scoreFont, "L");
		App->fonts->BlitText(position_clear_x + 30, position_clear_y, scoreFont, "E");
		App->fonts->BlitText(position_clear_x + 45, position_clear_y, scoreFont, "A");
		App->fonts->BlitText(position_clear_x + 60, position_clear_y, scoreFont, "R");
		App->fonts->BlitText(position_clear_x + 75, position_clear_y, scoreFont, "!");

		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();

	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(extraTexture, 63, 290, &world0);
	App->render->Blit(extraTexture, 56, 288, &p1);
	App->render->Blit(extraTexture, 168, 288, &p2);

	App->fonts->BlitText(positionx, positiony, scoreFont, "R");
	App->fonts->BlitText(positionx + 18, positiony, scoreFont, "O");
	App->fonts->BlitText(positionx + 36, positiony, scoreFont, "U");
	App->fonts->BlitText(positionx + 54, positiony, scoreFont, "N");
	App->fonts->BlitText(positionx + 72, positiony, scoreFont, "D");
	App->fonts->BlitText(position_num_x, position_num_y, scoreFont2, "1");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->fonts->Disable();
	App->particles->Disable();
	App->audio->PlayMusic(NULL, 1.0f);



	/*ERIC: ELIMINAR COSAS AL REEMPEZAR*/
	//App->player->CleanUp();
	//App->enemies->CleanUp();
	//App->particles->CleanUp();
	//App->collisions->CleanUp();
	//App->audio->CleanUp();
	return true;
}
