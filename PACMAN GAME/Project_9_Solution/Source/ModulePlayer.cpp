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

#include <stdio.h>

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

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 110;
	position.y = 214;

	destroyed = false;

	speed = 1;

	collider = App->collisions->AddCollider({ position.x, position.y, 14, 14 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=:&',.()x+-/@up*s·bt |#_>" };
	scoreFont = App->fonts->Load("Assets/Fonts/font1.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=>&',.()x+-/@*|#_:up· " };
	player1Font = App->fonts->Load("Assets/Fonts/font2.png", lookupTable2, 1);
	player2Font = App->fonts->Load("Assets/Fonts/font3.png", lookupTable2, 1);


	return ret;
}

Update_Status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	//if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	//{
	//	Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
	//	newParticle->collider->AddListener(this);
	//	App->audio->PlayFx(laserFx);
	//}

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
	
	App->fonts->BlitText(93, 22, scoreFont, scoreText);
	App->fonts->BlitText(13, 22, scoreFont, scoreText);
	App->fonts->BlitText(77, 14, scoreFont, "HIGH SCORE");
	App->fonts->BlitText(30, 14, player1Font, "1up");
	App->fonts->BlitText(173, 14, player2Font, "CREDIT");
	App->fonts->BlitText(197, 22, player2Font, "0");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;

		speed = 0;

	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
	{
		//if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		//&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		//&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		//&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE)
		//currentAnimation = &idleAnim;

		speed = -speed;

		//PostUpdate();

		//speed = 1;

	}
}