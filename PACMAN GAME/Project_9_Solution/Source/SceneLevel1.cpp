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
	App->collisions->AddCollider({ 17, 34, 201, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 42, 8, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 50, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 58, 8, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 98, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 106, 8, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 138, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 162, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 162, 8, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 202, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 210, 8, 48}, Collider::Type::WALL);
	App->collisions->AddCollider({ 9, 250, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 258, 8, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 258, 8, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 250, 23, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 225, 202, 7, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 201, 202, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 201, 162, 8, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 162, 23, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 138, 23, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 201, 98, 8, 49 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 98, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 225, 50, 7, 56 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 50, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 209, 42, 8, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 113, 42, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 65, 58, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 89, 66, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 41, 58, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 74, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 65, 82, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 49, 98, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 113, 74, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 89, 98, 56, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 58, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 66, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 185, 58, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 193, 74, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 161, 82, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 169, 98, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 49, 122, 24, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 161, 122, 24, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 49, 162, 24, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 161, 162, 24, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 89, 178, 56, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 113, 186, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 49, 202, 48, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 65, 210, 8, 16 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 127, 202, 48, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 161, 210, 8, 16 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 25, 226, 24, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 41, 234, 8, 16 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 65, 242, 32, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 89, 226, 8, 16 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 113, 226, 8, 40 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 137, 226, 8, 24 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 145, 242, 24, 8 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 185, 226, 8, 24 }, Collider::Type::WALL);
	/*App->collisions->AddCollider({ 193, 226, 16, 8 }, Collider::Type::WALL);*/

	//Letters animation


	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789." };
	scoreFont2 = App->fonts->Load("Assets/Fonts/Letters_Groups2.png", lookupTable2, 1);

	speedx = 5;
	speedy = 5;

	speed_num_x = 3;
	speed_num_y = 3;

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 110, 125);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 110, 125);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->fonts->Enable();
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 0;

	positionx -= speedx;
	positiony += speedy;

	position_num_x += speed_num_x;
	position_num_y -= speed_num_y;


	if (positiony > 130)
	{
		speedx = 0;
		speedy = -1;
	}

	if (position_num_y < 150)
	{
		speed_num_x = 0;
		speed_num_y = 1;
	}

	if (positiony < 100 && speedx == 0 && speedy == -1)
	{
		speedx = 5;
		speedy = 0;
	}

	if (position_num_y < 120 && speed_num_x == 0 && speed_num_y == 1)
	{
		speed_num_x = 5;
		speed_num_y = 0;
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
	App->fonts->BlitText(position_num_x, position_num_y, scoreFont2, "1");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{

	positionx = 255;
	positiony = -50;
	speedx = 0;
	speedy = 0;

	position_num_x = -20;
	position_num_y = 275;
	speed_num_x = 0;
	speed_num_y = 0;
	
	App->player->Disable();
	App->enemies->Disable();
	App->fonts->Disable();


	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}