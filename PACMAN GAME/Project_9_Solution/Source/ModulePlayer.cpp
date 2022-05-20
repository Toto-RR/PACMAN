#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"

#include <stdio.h>
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 161, 61, 16, 16 });
	idleAnim.PushBack({ 145, 62, 16, 16 });
	idleAnim.PushBack({ 129, 63, 16, 14 });
	idleAnim.loop = true;
	idleAnim.speed = 0.05f;

	// move upwards
	upAnim.PushBack({ 33, 61, 16, 16 });
	upAnim.PushBack({ 17, 62, 16, 16 });
	upAnim.PushBack({ 1, 63, 16, 14 });
	upAnim.loop = true;
	upAnim.speed = 0.05f;

	// Move down
	downAnim.PushBack({ 161, 78, 16, 15 });
	downAnim.PushBack({ 177, 78, 16, 15 });
	downAnim.PushBack({ 145, 78, 16, 15 });
	downAnim.loop = true;
	downAnim.speed = 0.05f;

	//Move right
	rightAnim.PushBack({ 81, 62, 16, 15 });
	rightAnim.PushBack({ 98, 61, 15, 16 });
	rightAnim.PushBack({ 65, 63, 16, 14 });
	rightAnim.loop = true;
	rightAnim.speed = 0.05f;

	//Move left
	leftAnim.PushBack({226,61,15,17});
	leftAnim.PushBack({209,62,16,16});
	leftAnim.PushBack({ 193,63,16,15 });
	leftAnim.loop = true;
	leftAnim.speed = 0.05f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Pac-Man/Pac-Man ripped.png");
	currentAnimation = &idleAnim;

//FX

	
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/Fx/life-lost.wav");



//Music
	Pacdot = App->audio->LoadFx("Assets/Music/Fx/wakka-3.wav");
	Superpacdot = App->audio->LoadFx("Assets/Music/Fx/wakka.wav");
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/Fx/life-lost.wav");

//>>>>>>> Stashed changes
	position.x = 110;
	position.y = 214;

	destroyed = false;


	state = speed_none;
	score = 0;

	collider = App->collisions->AddCollider({ position.x, position.y, 14, 14 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=:&',.()x+-/@up*s·bt |#_>" };
	scoreFont = App->fonts->Load("Assets/Fonts/font1.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=>&',.()x+-/@*|#_:up· " };
	player1Font = App->fonts->Load("Assets/Fonts/font2.png", lookupTable2, 1);
	player2Font = App->fonts->Load("Assets/Fonts/font3.png", lookupTable2, 1);


	//Animation start
	spawn.PushBack({ 240, 78, 15, 15 });
	spawn.PushBack({ 240, 78, 15, 15 });
	spawn.PushBack({ 240, 78, 15, 15 });
	spawn.PushBack({ 240, 78, 15, 15 });
	spawn.PushBack({ 240, 78, 15, 15 });
	spawn.PushBack({ 224, 78, 15, 15 });
	spawn.PushBack({ 208, 78, 15, 15 });
	spawn.PushBack({ 193, 78, 15, 15 });
	spawn.PushBack({ 1, 78, 15, 15 });
	spawn.PushBack({ 241, 62, 15, 15 });
	spawn.PushBack({ 209, 62, 15, 15 });
	spawn.PushBack({ 177, 62, 15, 15 });
	spawn.PushBack({ 145, 62, 15, 15 });
	spawn.PushBack({ 113, 62, 15, 15 });
	spawn.PushBack({ 81, 62, 15, 15 });
	spawn.PushBack({ 49, 62, 15, 15 });
	spawn.PushBack({ 1, 62, 15, 15 });




	currentAnimation = &spawn;

	spawn.loop = false;
	spawn.speed = 0.2f;

	return ret;
}

Update_Status ModulePlayer::Update()
{

	//PLAYER MOVEMENT

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		state = speed_left;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		state = speed_right;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN)
	{
		state = speed_up;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		state = speed_down;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	switch (state)
	{
		case speed_right:	position.x++;	break;
		case speed_left:	position.x--;	break;
		case speed_up:		position.y--;	break;
		case speed_down:	position.y++;	break;
	}
	
	//DEBUG FUNTIONS

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
		godMode = !godMode;

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
		App->particles->CleanUp();
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneGameOver, 90);
		App->particles->CleanUp();
	}


	// If no up/down movement detected, set the current animation back to idle
	//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE)
	//	currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();



	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{

	if (!destroyed)
	{
		
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(13, 22, scoreFont, scoreText);

	sprintf_s(scoreText, 10, "%7d", highScore);
	App->fonts->BlitText(93, 22, scoreFont, scoreText);

	App->fonts->BlitText(77, 14, scoreFont, "HIGH SCORE");
	App->fonts->BlitText(30, 14, player1Font, "1up");
	App->fonts->BlitText(173, 14, player2Font, "CREDIT");
	App->fonts->BlitText(197, 22, player2Font, "0");


	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY && destroyed == false && godMode != true)
	{
		App->particles->AddParticle(App->particles->death, position.x, position.y, Collider::Type::NONE, 2);


		if (state == 1)
		{
			position.x--;
		}

		else if (state == 2)
		{

			position.x++;

		}
		else if (state == 3)
		{

			position.y++;

		}
		else if (state == 4)
		{

			position.y--;

		}

		if (currentAnimation != &death) {
			death.PushBack({ 1, 62, 15, 15 });
			death.PushBack({ 49, 62, 15, 15 });
			death.PushBack({ 81, 62, 15, 15 });
			death.PushBack({ 113, 62, 15, 15 });
			death.PushBack({ 145, 62, 15, 15 });
			death.PushBack({ 177, 62, 15, 15 });
			death.PushBack({ 209, 62, 15, 15 });
			death.PushBack({ 241, 62, 15, 15 });
			death.PushBack({ 1, 78, 15, 15 });
			death.PushBack({ 193, 78, 15, 15 });
			death.PushBack({ 208, 78, 15, 15 });
			death.PushBack({ 224, 78, 15, 15 });
			death.PushBack({ 240, 78, 15, 15 });
			currentAnimation = &death;
			App->audio->PlayFx(explosionFx);
		}
		
		death.loop = false;
		death.speed = 0.09f;

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneGameOver, 90);
		App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneGameOver, 90);

		App->enemies->CleanUp();
		App->particles->CleanUp();


	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL && godMode != true)
	{

		if (state == 1)
		{
			position.x--;
		}

		if (state == 2)
		{
			
			position.x++;
			
		}
		if (state == 3)
		{
			
			position.y++;
			
		}
		if (state == 4)
		{
			
			position.y--;
			
		}
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SUPERPACDOT) {
		score += 50;
		if (highScore <= score)
			highScore = score;
		App->audio->PlayFx(Superpacdot);
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PACDOT) {
		score += 10;
		if (highScore <= score)
			highScore = score;
//<<<<<<< Updated upstream

		//App->audio->PlayFx(wakka);
		App->audio->LoadFx("Assets/Music/FX/Pacdot.wav");
//=======
		App->audio->PlayFx(Pacdot);

//>>>>>>> Stashed changes
	}
}

void ModulePlayer::RemovePacman(Collider* collider) 
{
	if (this->collider->PLAYER && collider->ENEMY)
	{
		destroyed = true;
	}
}