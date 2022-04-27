#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
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
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_level_0.png");

	extraTexture = App->textures->Load("Assets/Sprites/Extras_background.png");
	round = App->audio->LoadFx("Assets/Music/FX/round-start.wav");
	App->audio->PlayMusic("Assets/Music/Music/Toy Box World (World 0).ogg", 1.0f);

	//Level 1 Colliders
	App->collisions->AddCollider({ 17, 266, 201, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 34, 200, 9 }, Collider::Type::WALL);

	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	//Letters animation


	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	speedx = 5;
	speedy = 5;

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 110, 125);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 110, 125);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 0;

	positionx -= speedx;
	positiony += speedy;


	if (positiony > 130)
	{
		speedx = 0;
		speedy = -1;
	}

	if (positiony < 100 && speedx == 0 && speedy == -1)
	{
		speedx = 5;
		speedy = 0;
	}
	if (positiony == 50)
	{
		App->audio->PlayFx(round);
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
	//App->fonts->BlitText(positionx + 50, positiony + 10, scoreFont, "1");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{

	positionx = 255;
	positiony = -50;
	speedx = 0;
	speedy = 0;
	
	App->player->Disable();
	App->enemies->Disable();



	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}