#include "SceneLevel4.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL.h"

SceneLevel4::SceneLevel4(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel4::~SceneLevel4()
{

}

// Load assets
bool SceneLevel4::Start()
{

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_level_4.png");

	extraTexture = App->textures->Load("Assets/Sprites/Extras_background.png");
	


	//Music
	round = App->audio->LoadFx("Assets/Music/FX/round-start.wav");
	//App->audio->PlayFx(round);
	App->audio->PlayMusic("Assets/Music/Music/Original Pac-Man Maze (World 1).ogg", 25.0f);

	//Level 4 Colliders
	App->collisions->AddCollider({ 64, 55, 29, 20 }, Collider::Type::WALL);//Top left square
	App->collisions->AddCollider({ 136, 55, 29, 20 }, Collider::Type::WALL);//Top right square
	App->collisions->AddCollider({ 64, 239, 29, 20 }, Collider::Type::WALL);//Bottom left square
	App->collisions->AddCollider({ 136, 239, 29, 20 }, Collider::Type::WALL);//Bottom right square

	App->collisions->AddCollider({ 14, 25, 203, 13 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 14, 280, 203, 17 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1, 46, 6, 111 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 223, 46, 6, 111 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 23, 191, 23, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 183, 191, 23, 3 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 3, 32, 18, 19 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 208, 31, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 112, 34, 5, 43 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 184, 56, 5, 19 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 188, 71, 17, 4 }, Collider::Type::WALL);


	//Letters animation


	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789." };
	scoreFont2 = App->fonts->Load("Assets/Fonts/Letters_Groups2.png", lookupTable2, 1);

	speedx = 5;
	speedy = 5;

	speed_num_x = 3;
	speed_num_y = 3;

	//SuperPacdots ---

	//App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 11, 60);
	//App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 210, 60);
	//App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 11, 236);
	//App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 210, 236);

	////Pacdots ---

	//App->particles->AddPacdot(App->particles->PacdotAnim, 32, 40);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 50, 40);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 68, 40);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 86, 40);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 102, 40);

	//App->particles->AddPacdot(App->particles->PacdotAnim, 32, 56);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 13, 70);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 13, 82);

	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 70);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 82);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 94);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 106);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 118);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 130);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 142);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 154);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 78, 166);

	//App->particles->AddPacdot(App->particles->PacdotAnim, 28, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 41, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 53, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 65, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 77, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 89, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 101, 260);
	////App->particles->AddPacdot(App->particles->PacdotAnim, 113, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 125, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 137, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 149, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 161, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 173, 260);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 185, 260);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 121, 107);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 105, 107);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->fonts->Enable();
	App->collisions->Enable();


	return ret;
}

Update_Status SceneLevel4::Update()
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



	
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel4::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	/*SDL_Rect rc = {50, 50, 100, 100};	//x, y, w, h
	SDL_SetRenderDrawColor(App->render->renderer, 128, 192, 0, 128);
	SDL_RenderFillRect(App->render->renderer, &rc);*/
	
	App->render->Blit(extraTexture, 63, 290, &world1);
	App->render->Blit(extraTexture, 56, 288, &p1);
	App->render->Blit(extraTexture, 168, 288, &p2);



	App->fonts->BlitText(positionx, positiony, scoreFont, "R");
	App->fonts->BlitText(positionx + 18, positiony, scoreFont, "O");
	App->fonts->BlitText(positionx + 36, positiony, scoreFont, "U");
	App->fonts->BlitText(positionx + 54, positiony, scoreFont, "N");
	App->fonts->BlitText(positionx + 72, positiony, scoreFont, "D");
	App->fonts->BlitText(position_num_x, position_num_y, scoreFont2, "2");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel4::CleanUp()
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
	App->collisions->Disable();
	App->audio->PlayMusic(NULL, 1.0f);

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture (extraTexture);
	//delete App;
	
	return true;
}