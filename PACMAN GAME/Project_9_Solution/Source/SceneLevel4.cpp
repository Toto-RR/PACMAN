#include "SceneLevel4.h"


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
	App->sceneLevel_4->Enable();

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_level_4.png");

	extraTexture = App->textures->Load("Assets/Sprites/Extras_background.png");
	


	//Music
	round1 = App->audio->LoadFx("Assets/Music/FX/round-start.wav");
	clear = App->audio->LoadFx("Assets/Music/FX/round-clear.wav");
	App->audio->PlayFx(round1);
	App->audio->PlayMusic("Assets/Music/Music/Original Pac-Man Maze (World 1).ogg", 25.0f);

	//Letters animation
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ!'?-:/" };
	scoreFont = App->fonts->Load("Assets/Fonts/Letters_Groups.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789." };
	scoreFont2 = App->fonts->Load("Assets/Fonts/Letters_Groups2.png", lookupTable2, 1);

	speedx = 5;
	speedy = 5;

	speed_num_x = 3;
	speed_num_y = 3;

	App->particles->Enable();

	//Superpacdots---
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 25, 58);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 25, 248);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 196, 58);
	App->particles->AddSuperpacdot(App->particles->SuperPacdotAnim, 196, 248);


	//Pacdots ---

	//LEFT side
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 57);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 71);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 85);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 99);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 113);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 127);

	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 127);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 127);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 88, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 40);

	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 53);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 66);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 92);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 105);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 131);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 157);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 170);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 183);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 209);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 235);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 248);
	App->particles->AddPacdot(App->particles->PacdotAnim, 52, 261);

	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 246);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 232);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 218);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 204);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 190);
	App->particles->AddPacdot(App->particles->PacdotAnim, 12, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 26, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 39, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 88, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 78, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 247);

	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 52);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 65);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 91);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 65, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 77, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 88, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 131);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 157);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 170);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 183);
	App->particles->AddPacdot(App->particles->PacdotAnim, 74, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 100, 196);

	// RIGHT side
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 57);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 71);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 85);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 99);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 113);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 127);

	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 127);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 127);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 148);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 157, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 134, 40);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 40);

	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 53);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 66);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 79);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 92);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 105);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 131);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 157);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 170);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 183);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 209);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 235);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 248);
	App->particles->AddPacdot(App->particles->PacdotAnim, 170, 261);

	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 246);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 232);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 218);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 204);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 190);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 196, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 183, 176);
	App->particles->AddPacdot(App->particles->PacdotAnim, 157, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 134, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 261);
	App->particles->AddPacdot(App->particles->PacdotAnim, 157, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 146, 222);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 247);

	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 52);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 65);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 91);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 157, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 134, 78);
	App->particles->AddPacdot(App->particles->PacdotAnim, 133, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 104);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 118);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 131);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 157);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 170);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 183);
	App->particles->AddPacdot(App->particles->PacdotAnim, 145, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 133, 196);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 196);

	// Pineapple ---
	App->particles->AddPineapple(App->particles->PineappleAnim, 108, 172);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 105, 122);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 105, 107);
	App->enemies->AddEnemy(Enemy_Type::INKY, 105, 122);
	App->enemies->AddEnemy(Enemy_Type::PINKY, 105, 107);


	//for (int j = 0; j <= 28; ++j)
	//{
	//	for (int i = 0; i <= 37; ++i)
	//	{
	//		LOG("En %d,%d hay un %d", i, j, TileSet[i][j])
	//	}
	//}


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

	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN)
	{
		LOG("VICTORY");

		victory = true;

		//App->fade->FadeToBlack(this, (Module*)App->sceneLevel_4, 90);
		//App->audio->PlayMusic("Assets/Music/Result.ogg");

		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		//App->sceneLevel_1->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();

	}


	if (App->particles->COUNTDOWN <= 0)
	{

		LOG("VICTORY");
		victory = true;

		App->player->Disable();
		App->enemies->Disable();
		App->fonts->Disable();
		App->particles->Disable();
		App->audio->PlayMusic(NULL, 1.0f);
		App->collisions->CleanUp();

	}

	if (victory)
	{
		if (position_clear_y == 272)
		{
			App->audio->PlayFx(clear);
		}
		if (position_clear_y > 100)
		{
			position_clear_x += 2;
			position_clear_y -= 6;
		}
		if (position_clear_y < 105)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_F, 60);
		}

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
	App->sceneLevel_4->Disable();
	App->collisions->Disable();
	App->audio->PlayMusic(NULL, 1.0f);
	App->particles->Disable();

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture (extraTexture);
	//delete App;
	
	return true;
}