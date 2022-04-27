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
	App->collisions->AddCollider({ 113, 42, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 65, 58, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 34, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 50, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 50, 8, 56 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 138, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 98, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 98, 8, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 162, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 162, 8, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 202, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 202, 8, 56 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 250, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 250, 8, 24 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 209, 250, 8, 24 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 209, 250, 23, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 225, 202, 7, 56 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 209, 202, 16, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 209, 250, 8, 24 }, Collider::Type::WALL);
	/*App->collisions->AddCollider({ 201, 162, 8, 48 }, Collider::Type::WALL);*/
	/*App->collisions->AddCollider({ 201, 162, 31, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 201, 138, 31, 8 }, Collider::Type::WALL);*/
	App->collisions->AddCollider({ 201, 98, 8, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 201, 98, 31, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 225, 50, 7, 56 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 50, 23, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 34, 8, 24 }, Collider::Type::WALL);

	//Letters animation


	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	speedx = 5;
	speedy = 5;

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 100, 90);

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