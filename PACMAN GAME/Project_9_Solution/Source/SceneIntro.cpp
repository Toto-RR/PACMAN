#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	bgGhosts.PushBack({ 932, 0, 232, 305 });
	bgGhosts.PushBack({ 1165, 0, 232, 305 });
	bgGhosts.PushBack({ 1398, 0, 232, 305 });

	bgGhosts.PushBack({ 0, 306, 232, 305 });
	bgGhosts.PushBack({ 233, 306, 232, 305 });
	bgGhosts.PushBack({ 466, 306, 232, 305 });
	bgGhosts.PushBack({ 699, 306, 232, 305 });
	bgGhosts.PushBack({ 932, 306, 232, 305 });
	bgGhosts.PushBack({ 1165, 306, 232, 305 });
	bgGhosts.PushBack({ 1398, 306, 232, 305 });

	bgGhosts.PushBack({ 0, 612, 232, 305 });
	bgGhosts.PushBack({ 233, 612, 232, 305 });
	bgGhosts.PushBack({ 466, 612, 232, 305 });
	bgGhosts.PushBack({ 699, 612, 232, 305 });
	bgGhosts.PushBack({ 932, 612, 232, 305 });

	bgGhosts.speed = 0.05f;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/TitlescreenSpritesheet.png");

	GhostsAnimation = &bgGhosts;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	GhostsAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect rectGhosts = GhostsAnimation->GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rectGhosts);

	/*App->render->Blit(bgTexture, 0, 0, NULL);*/

	return Update_Status::UPDATE_CONTINUE;
}