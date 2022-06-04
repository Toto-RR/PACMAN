#include "GhostBlinky.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

GhostBlinky::GhostBlinky(int x, int y) : Enemy(x, y)
{
	if (App->sceneLevel_1->IsEnabled()) { LOG("PRESENTE") };

	up.PushBack({ 144, 0, 16, 15 });
	up.PushBack({ 160, 0, 16, 15 });
	up.PushBack({ 176, 0, 16, 15 });
	up.speed = 0.1f;
	up.loop = false;
	up.pingpong = true;

	down.PushBack({ 64, 0, 16, 15 });
	down.PushBack({ 80, 0, 16, 15 });
	down.PushBack({ 96, 0, 16, 15 });
	down.speed = 0.1f;
	down.loop = false;
	down.pingpong = true;


	rigth.PushBack({ 96, 0, 16, 15 });
	rigth.PushBack({ 112, 0, 16, 15 });
	rigth.PushBack({ 128, 0, 16, 15 });
	rigth.speed = 0.1f;
	rigth.loop = false;
	rigth.pingpong = true;


	left.PushBack({ 0, 0, 16, 15 });
	left.PushBack({ 16, 0, 16, 15 });
	left.PushBack({ 32, 0, 16, 15 });
	left.speed = 0.1f;
	left.loop = false;
	left.pingpong = true; 

	currentAnim = &up;
	currentDirection = UP;
	currentMode = FEAR;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}



void GhostBlinky::Update()
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation(); //hacer paths de 0 speed para cambiar la anim

	++timer;
	if (timer < 1)
	{

	}


	//TILE UPDATER (tile.x coresponds to height and tile .y corresponds to lenght)
	if ((int)position.x % 8 == 0)
	{
		tile.y = (position.x / 8);
	}
	if ((int)position.y % 8 == 0)
	{
		tile.x = (position.y / 8);
	}

	tileUp.x = tile.x - 1;
	tileUp.y = tile.y;

	tileDown.x = tile.x + 2;
	tileDown.y = tile.y;

	tileLeft.x = tile.x;
	tileLeft.y = tile.y - 1;

	tileRight.x = tile.x;
	tileRight.y = tile.y + 2;

	if (changeTimer >= 20)
	{
		changeLimit = false;
	}

	switch (currentMode)
	{


	case GhostBlinky::CHASE:

		objectives = App->player->position;
		switch (currentDirection)
		{
		case GhostBlinky::UP:
			break;
		case GhostBlinky::LEFT:
			break;
		case GhostBlinky::DOWN:
			break;
		case GhostBlinky::RIGTH:
			break;
		default:
			break;
		}


		break;
	case GhostBlinky::SCATTER:


		break;
	case GhostBlinky::FEAR:

		//ERIC: Cada iteracion pasa por aqui, hay que limitar que si hay un cambio complato de direccion sea una sola vez
		LOG("panik activated");

		switch (currentDirection)
		{
			++changeTimer;
		case GhostBlinky::UP:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y -= movSpeed;
				currentAnim = &up;

			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;


				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = LEFT;


					break;
				}
			}

			if (App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST && (int)position.x % 8 == 0
				&& (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;


				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = RIGTH;

					changeLimit = true;
					break;
				}
			}

			//CHOQUE CON PARED
			if ((App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
			{


				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					currentDirection = LEFT;

					break;
				case(1):
					currentDirection = RIGTH;

					break;

				}

				//Pared Izquierda--> Derecha
				if ((App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if ((App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}

			break;
		}


		case GhostBlinky::LEFT:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
			{
				position.x -= movSpeed;
				currentAnim = &left;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;



				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = UP;

					break;
				}
			}

			if ((App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{

				changeLimit = true;
				changeTimer = 0;



				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = DOWN;

					break;
				}
			}

			//CHOQUE CON PARED
			if ((App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
			{



				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					currentDirection = UP;

					break;
				case(1):
					currentDirection = DOWN;

					break;
				}

				//Pared alta--> Baja
				if ((App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared bajo--> Alta
				if ((App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}

			}
			break;
		}


		case GhostBlinky::DOWN:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y += movSpeed;
				currentAnim = &down;

			}

			//CAMBIAR DIRECCION EN UN CRUCE


			if ((App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;


				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = LEFT;

					break;
				}
			}

			if ((App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;



				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = RIGTH;

					break;
				}
			}

			//CHOQUE CON PARED
			if (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
			{

				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					currentDirection = LEFT;

					break;
				case(1):
					currentDirection = RIGTH;

					break;
				}

				//Pared Izquierda--> Derecha
				if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if (App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}
			break;
		}

		case GhostBlinky::RIGTH:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[0][tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[0][tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
			{
				position.x += movSpeed;
				currentAnim = &rigth;
			}


			//CAMBIAR DIRECCION EN UN CRUCE



			if ((App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;



				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = UP;

					break;
				}
			}

			if ((App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[0][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{

				changeLimit = true;
				changeTimer = 0;


				newDir = rand() % 2;
				switch (newDir)
				{

				case(0):
					//Continue going
					break;
				case(1):
					currentDirection = DOWN;

					break;
				}
			}

			//CHOQUE CON PARED
			if ((App->sceneLevel_1->TileSet[0][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
			{


				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					currentDirection = UP;

					break;
				case(1):
					currentDirection = DOWN;

					break;
				}

				//Pared ARRIBA--> Baja
				if (App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared abajo--> Sube
				if (App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[0][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}
			}
			break;
		}



		default:
			break;
		}



		break;
	case GhostBlinky::EATEN:
		break;
	default:
		break;
	}

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->render->Blit(texture, (int)position.x, (int)position.y, &rect);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}


