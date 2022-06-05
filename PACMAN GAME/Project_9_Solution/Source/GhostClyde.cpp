#include "GhostClyde.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

GhostClyde::GhostClyde(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 160, 0, 15, 15 });
	up.PushBack({ 160, 1, 16, 15 });
	currentAnim = &up;
	up.loop = true;
	up.speed = 0.05f;
	
	down.PushBack({ 65, 0, 15, 15 });
	down.PushBack({ 65, 1, 16, 15 });
	currentAnim = &down;
	down.loop = true;
	down.speed = 0.05f;

	rigth.PushBack({ 111, 0, 15, 15 });
	rigth.PushBack({ 111, 1, 15, 15 });
	currentAnim = &rigth;
	rigth.loop = true;
	rigth.speed = 0.05f;

	left.PushBack({ 16, 0, 15, 15 });
	left.PushBack({ 16, 1, 15, 15 });
	currentAnim = &left;
	left.loop = true;
	left.speed = 0.05f;

	/*path.PushBack({ 0.5f, 0.0f }, 130, &right);
	path.PushBack({ 0.0f, 0.5f }, 208, &down);
	path.PushBack({ -0.5f, 0.0f }, 32, &left);
	path.PushBack({ 0.0f, 0.5f }, 32, &down);
	path.PushBack({ -0.5f, 0.0f }, 48, &left);
	path.PushBack({ 0.0f, -0.5f }, 32, &up);
	path.PushBack({ -0.5f, 0.0f }, 94, &left);
	path.PushBack({ 0.0f, -0.5f }, 48, &up);
	path.PushBack({ -0.5f, 0.0f }, 48, &left);
	path.PushBack({ 0.0f, -0.5f }, 159, &up);
	path.PushBack({ 0.5f, 0.0f }, 94, &right);*/
	
	currentAnim = &up;
	currentDirection = UP;
	currentMode = FEAR;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void GhostClyde::Update()
{
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


	case GhostClyde::CHASE:

		objectives = App->player->position;
		switch (currentDirection)
		{
		case GhostClyde::UP:
			break;
		case GhostClyde::LEFT:
			break;
		case GhostClyde::DOWN:
			break;
		case GhostClyde::RIGTH:
			break;
		default:
			break;
		}


		break;
	case GhostClyde::SCATTER:


		break;
	case GhostClyde::FEAR:

		//ERIC: Cada iteracion pasa por aqui, hay que limitar que si hay un cambio complato de direccion sea una sola vez
		LOG("panik activated");

		switch (currentDirection)
		{
			++changeTimer;
		case GhostClyde::UP:
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


		case GhostClyde::LEFT:
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


		case GhostClyde::DOWN:
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

		case GhostClyde::RIGTH:
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
	case GhostClyde::EATEN:
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