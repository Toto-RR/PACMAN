#include "GhostInky.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"


GhostInky::GhostInky(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 160, 35, 15, 15 });
	up.PushBack({ 160, 36, 15, 15 });
	currentAnim = &up;
	up.loop = true;
	up.speed = 0.05f;

	down.PushBack({ 65, 35, 15, 15 });
	down.PushBack({ 65, 36, 15, 15 });
	currentAnim = &down;
	down.loop = true;
	down.speed = 0.05f;

	rigth.PushBack({ 111, 35, 15, 15 });
	rigth.PushBack({ 111, 36, 15, 15 });
	currentAnim = &rigth;
	rigth.loop = true;
	rigth.speed = 0.05f;
	
	left.PushBack({ 16, 35, 15, 15 });
	left.PushBack({ 16, 36, 15, 15 });
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

	currentAnim = &down;
	currentDirection = DOWN;
	currentMode = FEAR;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void GhostInky::Update()
{
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();*/

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


	case GhostInky::CHASE:

		objectives = App->player->position;
		switch (currentDirection)
		{
		case GhostInky::UP:
			break;
		case GhostInky::LEFT:
			break;
		case GhostInky::DOWN:
			break;
		case GhostInky::RIGTH:
			break;
		default:
			break;
		}


		break;
	case GhostInky::SCATTER:


		break;
	case GhostInky::FEAR:

		//ERIC: Cada iteracion pasa por aqui, hay que limitar que si hay un cambio complato de direccion sea una sola vez
		LOG("panik activated");

		switch (currentDirection)
		{
			++changeTimer;
		case GhostInky::UP:
			//SEGUIR DE FRENTE SIN PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY)
			{
				position.y -= movSpeed;
				currentAnim = &up;
			}
			//GIRAR SI HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->WALL)
			{
				//SI HAY PARED EN LA IZQUIERDA IRÁ A DERECHA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY) izquierda = true;
				else currentDirection = RIGTH;

				//SI HAY PARED EN LA DERECHA IRÁ A IZQUIERDA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY) derecha = true;
				else currentDirection = LEFT;

				//SI NO HAY PAREDES A LOS LADOS
				if (izquierda == true && derecha == true)
				{
					newDir = rand() % 2;
					if (newDir == 0) currentDirection = LEFT;
					if (newDir == 0) currentDirection = RIGTH;
				}
			}

			//SALIDA DE FRENTE O A LA IZQUIERDA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = UP;
				if (newDir == 0) currentDirection = LEFT;
			}

			//SALIDA DE FRENTE O A LA DERECHA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = UP;
				if (newDir == 0) currentDirection = RIGTH;
			}
			break;

		case GhostInky::DOWN:
			//SEGUIR DE FRENTE SIN PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY)
			{
				position.y += movSpeed;
				currentAnim = &down;
			}
			
			//GIRAR SI HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->WALL)
			{
				//SI HAY PARED EN LA IZQUIERDA IRÁ A DERECHA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY) izquierda = true;
				else currentDirection = RIGTH;

				//SI HAY PARED EN LA DERECHA IRÁ A IZQUIERDA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY) derecha = true;
				else currentDirection = LEFT;

				//SI NO HAY PAREDES A LOS LADOS
				if (izquierda == true && derecha == true)
				{
					newDir = rand() % 2;
					if (newDir == 0) currentDirection = LEFT;
					if (newDir == 0) currentDirection = RIGTH;
				}
			}

			//SALIDA DE FRENTE O A LA IZQUIERDA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = DOWN;
				if (newDir == 0) currentDirection = LEFT;
			}

			//SALIDA DE FRENTE O A LA DERECHA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = DOWN;
				if (newDir == 0) currentDirection = RIGTH;
			}
			break;

		case GhostInky::LEFT:
			//SEGUIR DE FRENTE SIN PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				position.x -= movSpeed;
				currentAnim = &left;
			}

			//GIRAR SI HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->WALL)
			{
				//SI HAY PARED EN LA ARRIBA IRÁ A ABAJO
				if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY) arriba = true;
				else currentDirection = DOWN;

				//SI HAY PARED EN LA DERECHA IRÁ A IZQUIERDA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY) abajo = true;
				else currentDirection = UP;

				//SI NO HAY PAREDES A LOS LADOS
				if (arriba == true && abajo == true)
				{
					newDir = rand() % 2;
					if (newDir == 0) currentDirection = UP;
					if (newDir == 0) currentDirection = DOWN;
				}
			}

			//SALIDA DE FRENTE O ABAJO
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = DOWN;
				if (newDir == 0) currentDirection = LEFT;
			}

			//SALIDA DE FRENTE O ARRIBA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x - 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = UP;
				if (newDir == 0) currentDirection = LEFT;
			}
			break;

		case GhostInky::RIGTH:
			//SEGUIR DE FRENTE SIN PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				position.x += movSpeed;
				currentAnim = &rigth;
			}

			//GIRAR SI HAY PARED
			if (App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL)
			{
				//SI HAY PARED EN LA ARRIBA IRÁ A ABAJO
				if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY) arriba = true;
				else currentDirection = DOWN;

				//SI HAY PARED EN LA DERECHA IRÁ A IZQUIERDA
				if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY) abajo = true;
				else currentDirection = UP;

				//SI NO HAY PAREDES A LOS LADOS
				if (arriba == true && abajo == true)
				{
					newDir = rand() % 2;
					if (newDir == 0) currentDirection = UP;
					if (newDir == 0) currentDirection = DOWN;
				}
			}

			//SALIDA DE FRENTE O ABAJO
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y + 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = DOWN;
				if (newDir == 0) currentDirection = RIGTH;
			}

			//SALIDA DE FRENTE O ARRIBA
			if (App->sceneLevel_1->TileSet[0][tileLeft.x][tileLeft.y - 1] == App->sceneLevel_1->EMPTY &&
				App->sceneLevel_1->TileSet[0][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->EMPTY)
			{
				newDir = rand() % 2;
				if (newDir == 0) currentDirection = UP;
				if (newDir == 0) currentDirection = RIGTH;
			}
			break;

		default:
			break;
		}
		break;
	case GhostInky::EATEN:
		break;
	default:
		break;
	}

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->render->Blit(texture, (int)position.x, (int)position.y, &rect);
	Enemy::Update();
}