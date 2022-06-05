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

	/*App->particles->AddPacdot(App->particles->PacdotAnim, 37, 82);
	App->particles->AddParticle(App->particles->SuperPacdotAnim, 37, 96);
	App->particles->AddParticle(App->particles->PacdotAnim, 37, 108);*/

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 115 , 133); 
	App->enemies->AddEnemy(Enemy_Type::INKY, 104, 136);
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 145, 133);
	//App->enemies->AddEnemy(Enemy_Type::PINKY, 104, 120);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->fonts->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	
	/*App->render->camera.x += 15;*/

	if (App->particles->COUNTDOWN <= 0)
	{
		LOG("VICTORY");
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
		
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 30);
		App->audio->PlayMusic("Assets/Music/Result.ogg");
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
