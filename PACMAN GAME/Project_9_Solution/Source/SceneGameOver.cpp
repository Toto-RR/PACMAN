#include "SceneGameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

SceneGameOver::SceneGameOver(bool startEnabled) : Module(startEnabled)
{

}

SceneGameOver::~SceneGameOver()
{

}

// Load assets
bool SceneGameOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/game over.png");
	App->player->Disable();
	App->collisions->CleanUp();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}



Update_Status SceneGameOver::Update()
{
	App->render->camera.x += 0;

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}