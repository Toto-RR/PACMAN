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

	//Music
	round = App->audio->LoadFx("Assets/Music/FX/opening-fanfare.wav");
	App->audio->PlayFx(round);
	App->audio->PlayMusic("Assets/Music/Music/Toy Box World (World 0).ogg", 25.0f);

	//PRINT COLIDERS PAREDES
	for (int j = 0; j <= 28; ++j)
	{
		for (int i = 0; i <= 37; ++i)
		{
			LOG("En %d,%d hay un %d", i, j, TileSet[i][j])
		}
	}
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 82);

	// Enemies ---
	/*App->enemies->AddEnemy(Enemy_Type::BLINKY, 112, 136); 
	App->enemies->AddEnemy(Enemy_Type::INKY, 104, 136);
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 104, 128);
	App->enemies->AddEnemy(Enemy_Type::PINKY, 104, 120);*/

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	/*App->render->camera.x += 15;*/

	/*if (App->particles->COUNTDOWN <= 0)
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
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneGameOver, 30);
		App->audio->PlayMusic("Assets/Music/Ending.ogg");
	}*/

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// ERIC: ELIMINAR COSAS AL REEMPEZAR
	App->player->CleanUp();
	App->enemies->CleanUp();
	App->particles->CleanUp();
	App->collisions->CleanUp();
	App->audio->CleanUp();
	return true;
}
