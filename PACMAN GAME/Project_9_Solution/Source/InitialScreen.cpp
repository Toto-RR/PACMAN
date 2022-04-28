#include "InitialScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

InitialScreen::InitialScreen(bool startEnabled) : Module(startEnabled)
{

}

InitialScreen::~InitialScreen()
{

}

// Load assets
bool InitialScreen::Start()
{
	LOG("Loading background1 assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Initial_Background.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status InitialScreen::Update()
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
Update_Status InitialScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	//SDL_Rect rectGhosts = GhostsAnimation->GetCurrentFrame();
	//App->render->Blit(bgTexture, 0, 0, &rectGhosts);
	App->render->Blit(bgTexture, 0, 0, NULL);


	return Update_Status::UPDATE_CONTINUE;
}