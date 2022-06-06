#include "SceneLevelFinal.h"

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

SceneLevelFinal::SceneLevelFinal(bool startEnabled) : Module(startEnabled)
{

}

SceneLevelFinal::~SceneLevelFinal()
{

}

// Load assets
bool SceneLevelFinal::Start()
{

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Final_Level_.png");

	extraTexture = App->textures->Load("Assets/Sprites/Extras_background.png");

	
	//Music
	round1 = App->audio->LoadFx("Assets/Music/FX/round-start.wav");
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

	//Pacdots
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 108);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 206);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 218);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 230);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 242);

	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 108);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 138);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 200);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 212);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 224);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 236);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 245);

	/*App->particles->AddPacdot(App->particles->PacdotAnim, 80, 93);*/
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 108);
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 120);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 80, 131);
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 206);
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 218);
	App->particles->AddPacdot(App->particles->PacdotAnim, 80, 230);
	/*App->particles->AddPacdot(App->particles->PacdotAnim, 80, 242);*/

	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 108);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 120);
	/*App->particles->AddPacdot(App->particles->PacdotAnim, 112, 131);*/
	//App->particles->AddPacdot(App->particles->PacdotAnim, 112, 144);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 206);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 218);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 230);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 242);
	App->particles->AddPacdot(App->particles->PacdotAnim, 112, 245);

	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 108);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 120);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 136, 131);
	//App->particles->AddPacdot(App->particles->PacdotAnim, 136, 141);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 203);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 215);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 227);
	App->particles->AddPacdot(App->particles->PacdotAnim, 136, 239);

	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 105);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 117);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 128);
	/*App->particles->AddPacdot(App->particles->PacdotAnim, 168, 138);*/
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 200);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 212);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 224);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 236);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 245);


	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 36, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 99, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 111, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 135, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 147, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 159, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 125);

	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 36, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 93, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 105, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 117, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 129, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 141, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 153, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 168, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 180, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 192, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 204, 160);
	App->particles->AddPacdot(App->particles->PacdotAnim, 216, 160);

	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 36, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 99, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 111, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 135, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 147, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 159, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 184);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 184);

	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 36, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 99, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 111, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 135, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 147, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 159, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 210, 216);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 216);

	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 99, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 111, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 135, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 147, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 159, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 93);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 93);

	App->particles->AddPacdot(App->particles->PacdotAnim, 48, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 60, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 75, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 87, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 99, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 111, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 123, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 135, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 147, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 159, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 174, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 186, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 198, 245);
	App->particles->AddPacdot(App->particles->PacdotAnim, 200, 245);

	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 137);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 149);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 161);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 173);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 185);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 197);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 210);
	App->particles->AddPacdot(App->particles->PacdotAnim, 24, 216);

	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 125);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 137);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 149);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 161);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 173);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 185);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 197);
	App->particles->AddPacdot(App->particles->PacdotAnim, 222, 210);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::CLYDE, 104, 107);
	App->enemies->AddEnemy(Enemy_Type::BLINKY, 16, 107);
	//App->enemies->AddEnemy(Enemy_Type::PINKY, 35, 107);
	App->enemies->AddEnemy(Enemy_Type::INKY, 98, 107);

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

Update_Status SceneLevelFinal::Update()
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
Update_Status SceneLevelFinal::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	/*SDL_Rect rc = {50, 50, 100, 100};	//x, y, w, h
	SDL_SetRenderDrawColor(App->render->renderer, 128, 192, 0, 128);
	SDL_RenderFillRect(App->render->renderer, &rc);*/

	App->render->Blit(extraTexture, 90, 288, &world1);
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

bool SceneLevelFinal::CleanUp()
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
	App->sceneLevel_1->Disable();
	App->particles->Disable();
	App->collisions->Disable();
	App->audio->PlayMusic(NULL, 1.0f);

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(extraTexture);
	//delete App;

	return true;
}