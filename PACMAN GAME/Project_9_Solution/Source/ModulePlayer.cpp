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
#include "SceneLevel1.h"
#include "SceneLevel4.h"
#include "SceneLevelFinal.h"
#include "GhostInky.h"

#include <stdio.h>
#include <chrono>
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 161, 61, 16, 16 });
	idleAnim.PushBack({ 145, 62, 16, 16 });
	idleAnim.PushBack({ 129, 63, 16, 14 });
	idleAnim.loop = true;
	idleAnim.speed = 0.2f;

	// move upwards
	upAnim.PushBack({ 33, 61, 16, 16 });
	upAnim.PushBack({ 17, 62, 16, 16 });
	upAnim.PushBack({ 1, 63, 16, 14 });
	upAnim.loop = true;
	upAnim.speed = 0.2f;

	// Move down
	downAnim.PushBack({ 161, 78, 16, 15 });
	downAnim.PushBack({ 177, 78, 16, 15 });
	downAnim.PushBack({ 145, 78, 16, 15 });
	downAnim.loop = true;
	downAnim.speed = 0.2f;

	//Move right
	rightAnim.PushBack({ 81, 62, 16, 15 });
	rightAnim.PushBack({ 98, 61, 15, 16 });
	rightAnim.PushBack({ 65, 63, 16, 14 });
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

	//Move left
	leftAnim.PushBack({ 226,61,15,17 });
	leftAnim.PushBack({ 209,62,16,16 });
	leftAnim.PushBack({ 193,63,16,15 });
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

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

	//Music
	Superpacdot = App->audio->LoadFx("Assets/Music/Fx/wakka.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/Fx/life-lost.wav");
	Pacdot = App->audio->LoadFx("Assets/Music/FX/Pacdot.wav");
	Pineapple = App->audio->LoadFx("Assets/Music/Fx/fruit-eaten.wav");

	position.x = 110;
	position.y = 214;

	devourer = false;

	score = 0;

	collider = App->collisions->AddCollider({ (int)position.x + 1, (int)position.y + 1, 16, 16 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=:&',.()x+-/@up*s·bt |#_>" };
	scoreFont = App->fonts->Load("Assets/Fonts/font1.png", lookupTable, 1);

	char lookupTable2[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!<?=>&',.()x+-/@*|#_:up· " };
	player1Font = App->fonts->Load("Assets/Fonts/font2.png", lookupTable2, 1);
	player2Font = App->fonts->Load("Assets/Fonts/font3.png", lookupTable2, 1);

	tile.y = 26;
	tile.x = 14;
	position.x = tile.x * 8;
	position.y = tile.y * 8;

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if ((int)position.x % 8 == 0)
	{
		tile.y = (position.x / 8);
	}
	if ((int)position.y % 8 == 0)
	{
		tile.x = (position.y / 8);
	}

	//Movement posibilities
	//LAS X SON LA ALTURA DENTRO DEL TILESET MIENTAS QUE LAS Ys SON LA LONGUITUD
	tileUp.x = tile.x - 1;
	tileUp.y = tile.y;

	tileDown.x = tile.x + 2;
	tileDown.y = tile.y;

	tileLeft.x = tile.x;
	tileLeft.y = tile.y - 1;

	tileRight.x = tile.x;
	tileRight.y = tile.y + 2;


	//MOVIMIENTO IZQUIERDA
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || MovingLeft == true)
	{
		if (App->sceneLevel_1->IsEnabled())
		{
			if ((App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->EMPTY) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = true;
				MovingRight = false;
				position.x -= speed;

				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}

			}
		}
		//IT CAN MOVE INTO TP AN PAST IT

		else if (App->sceneLevel_4->IsEnabled())
		{
			if ((App->sceneLevel_4->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->EMPTY) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y + 2] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y + 2] == App->sceneLevel_4->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = true;
				MovingRight = false;
				position.x -= speed;

				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}

			}
		}
		else if (App->sceneLevel_F->IsEnabled())
		{
			if ((App->sceneLevel_F->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_F->EMPTY && App->sceneLevel_F->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_F->EMPTY) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_F->TP) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_F->TP) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y + 2] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y + 2] == App->sceneLevel_F->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = true;
				MovingRight = false;
				position.x -= speed;

				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}

			}
		}

	}

	//MOVIMIENTO DERECHA
	if ((App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) || MovingRight == true)
	{
		if (App->sceneLevel_1->IsEnabled())
		{
			if ((App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->EMPTY) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = true;
				position.x += speed;

				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
				}

			}
		}
		//IT CAN MOVE INTO TP AN PAST IT

		else if (App->sceneLevel_4->IsEnabled())
		{
			if ((App->sceneLevel_4->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->EMPTY) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[0][tile.x][tile.y - 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[0][tile.x + 1][tile.y - 1] == App->sceneLevel_4->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = true;
				position.x += speed;

				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
				}

			}
		}

		else if (App->sceneLevel_F->IsEnabled())
		{
			if ((App->sceneLevel_F->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_F->EMPTY && App->sceneLevel_F->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_F->EMPTY) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_F->TP) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_F->TP) ||
				(App->sceneLevel_F->TileSet[0][tile.x][tile.y - 1] == App->sceneLevel_F->TP && App->sceneLevel_F->TileSet[0][tile.x + 1][tile.y - 1] == App->sceneLevel_F->TP))
			{
				MovingUp = false;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = true;
				position.x += speed;

				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
				}

			}
		}

	}

	//MOVIMIENTO ABAJO
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || MovingDown == true)
	{
		if (App->sceneLevel_1->IsEnabled())
		{
			if (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y + 1] >= App->sceneLevel_1->EMPTY)
			{
				MovingUp = false;
				MovingDown = true;
				MovingLeft = false;
				MovingRight = false;
				position.y += speed;

				if (currentAnimation != &downAnim)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
				}

			}
		}

		else if (App->sceneLevel_4->IsEnabled())
		{
			if (App->sceneLevel_4->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_4->EMPTY &&
				App->sceneLevel_4->TileSet[0][tileDown.x][tileDown.y + 1] >= App->sceneLevel_4->EMPTY)
			{
				MovingUp = false;
				MovingDown = true;
				MovingLeft = false;
				MovingRight = false;
				position.y += speed;

				if (currentAnimation != &downAnim)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
				}

			}
		}

		else if (App->sceneLevel_F->IsEnabled())
		{
			if (App->sceneLevel_F->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_F->EMPTY &&
				App->sceneLevel_F->TileSet[0][tileDown.x][tileDown.y + 1] >= App->sceneLevel_F->EMPTY)
			{
				MovingUp = false;
				MovingDown = true;
				MovingLeft = false;
				MovingRight = false;
				position.y += speed;

				if (currentAnimation != &downAnim)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
				}

			}
		}


	}

	//MOVIMIENTO ARRIBA
	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || MovingUp == true)
	{

		if (App->sceneLevel_1->IsEnabled())
		{
			if (App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y + 1] >= App->sceneLevel_1->EMPTY)
			{
				MovingUp = true;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = false;
				position.y -= speed;

				if (currentAnimation != &upAnim)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
				}
			}
		}
		else if (App->sceneLevel_4->IsEnabled())
		{
			if (App->sceneLevel_4->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_4->EMPTY &&
				App->sceneLevel_4->TileSet[0][tileUp.x][tileUp.y + 1] >= App->sceneLevel_4->EMPTY)
			{
				MovingUp = true;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = false;
				position.y -= speed;

				if (currentAnimation != &upAnim)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
				}
			}
		}
		
		else if (App->sceneLevel_F->IsEnabled())
		{
			if (App->sceneLevel_F->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_F->EMPTY &&
				App->sceneLevel_F->TileSet[0][tileUp.x][tileUp.y + 1] >= App->sceneLevel_F->EMPTY)
			{
				MovingUp = true;
				MovingDown = false;
				MovingLeft = false;
				MovingRight = false;
				position.y -= speed;

				if (currentAnimation != &upAnim)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
				}
			}
		}


	}

	//TP
	if (position.x <= -8)
	{
		position.x = 232;
	}
	if (position.x >= 236)
	{
		position.x = -4;
	}

	//God mode: Inmunity agaist ghosts
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) 
	{
		if (godMode == false)
			godMode = true;
		else
		{
			godMode = false;
		}

	};

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
	{
		godMode = false;
		collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 14, 14 }, Collider::Type::ENEMY, this);
		App->audio->PlayMusic("Assets/Music/Ending.ogg");
	};
	
	
	collider->SetPos((int)position.x, (int)position.y);
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
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY && destroyed == false && godMode != true && devourer == false)
	{
		/*App->particles->AddSuperpacdot(App->particles->death, position.x, position.y, Collider::Type::NONE, 2);*/
		MovingDown = false;
		MovingLeft = false;
		MovingRight = false;
		MovingUp = false;
		
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
			death.PushBack({ 240, 94, 15, 15 });
			currentAnimation = &death;
			App->audio->PlayFx(explosionFx);
			death.loop = false;
			death.pingpong = false;
			death.speed = 0.16f;
		}
		

		if (App->sceneLevel_1->IsEnabled())
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneGameOver, 90);
		}
		else if (App->sceneLevel_4->IsEnabled())
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneGameOver, 90);
		}
		else if (App->sceneLevel_F->IsEnabled()) 
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_F, (Module*)App->sceneGameOver, 90);
		}
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY && destroyed == false && devourer == true) 
	{
		score += 200;
		devourer = false;
		speed = 0.8;
	}


	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PINEAPPLE) {
		score += 100;
		if (highScore <= score)
			highScore = score;
		App->audio->PlayFx(Pineapple);
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SUPERPACDOT) {
		score += 50;
		if (highScore <= score)
			highScore = score;
		App->audio->PlayFx(Superpacdot);
		devourer = true;
		speed = 0.8;
		
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PACDOT) {
		score += 10;
		if (highScore <= score)
			highScore = score;
		App->audio->PlayFx(Pacdot);
	}
}

void ModulePlayer::RemovePacman(Collider* collider)
{
	if (this->collider->PLAYER && collider->ENEMY)
	{
		destroyed = true;
	
	}
}