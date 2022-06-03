#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

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

	

	//Music
	round = App->audio->LoadFx("Assets/Music/FX/opening-fanfare.wav");
	App->audio->PlayFx(round);
	App->audio->PlayMusic("Assets/Music/Music/Toy Box World (World 0).ogg", 25.0f);

	//Level 1 Colliders
	App->collisions->AddCollider({ 17, 266, 201, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 17, 34, 201, 8 }, Collider::Type::WALL);
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
	App->collisions->AddCollider({ 137, 202, 48, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 161, 210, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 25, 226, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 41, 234, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 65, 242, 32, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 89, 226, 8, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 113, 229, 8, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 226, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 145, 242, 24, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 185, 226, 8, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 193, 226, 16, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 89, 122, 8, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 97, 154, 40, 5 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 122, 8, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 97, 122, 8, 5 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 129, 122, 8, 5 }, Collider::Type::WALL);

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

	App->particles->AddParticle(App->particles->SuperPacdotAnim, 11, 60);
	App->particles->AddParticle(App->particles->SuperPacdotAnim, 210, 60);
	App->particles->AddParticle(App->particles->SuperPacdotAnim, 11, 236);
	App->particles->AddParticle(App->particles->SuperPacdotAnim, 210, 236);
	
	//Pacdots ---

	App->particles->AddPacdot(App->particles->PacdotAnim, 32, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 50, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 68, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 86, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 102, 40);

	App->particles->AddPacdot(App->particles->PacdotAnim, 32, 56);
	App->particles->AddPacdot(App->particles->PacdotAnim, 13, 70);
	App->particles->AddPacdot(App->particles->PacdotAnim, 13, 82);
	
	//COLUMNA IZQUIERDA
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 94);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 130);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 142);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 154);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 166);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 178);
	App->particles->AddPacdot(App->particles->PacdotAnim, 37, 190);

	//COLUMNA DERECHA
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 82);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 94);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 106);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 130);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 142);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 154);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 166);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 178);
	App->particles->AddPacdot(App->particles->PacdotAnim, 189, 190);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 121, 107);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 105, 107);
	App->enemies->AddEnemy(Enemy_Type::INKY, 103, 107);
	App->enemies->AddEnemy(Enemy_Type::PINKY, 109, 107);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->fonts->Enable();
	App->collisions->Enable();
	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (!level_up)
	{
		App->render->camera.x += 0;

		positionx -= speedx;
		positiony += speedy;

		position_num_x += speed_num_x;
		position_num_y -= speed_num_y;

		//position_clear_x++;
		//position_clear_x2--;
		//position_clear_y -= 2;
	

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
	
		if (App->player->score >= 100)
		{
			level_up = true;
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
			App->enemies->CleanUp();
			App->particles->CleanUp();
			//App->sceneLevel_1->CleanUp();
		}
	}
	else
	{
		//waiting to fade to next level
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
	position_clear_x = 50;
	
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

