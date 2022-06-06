#include "GhostBlinky.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "SceneLevel4.h"
#include "SceneLevelFinal.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

GhostBlinky::GhostBlinky(int x, int y) : Enemy(x, y)
{
	if (App->sceneLevel_1->IsEnabled()) { LOG("PRESENTE") };


	up.PushBack({ 144, 36, 15, 15 });
	up.PushBack({ 160, 36, 15, 15 });
	up.PushBack({ 176, 36, 15, 15 });
	up.speed = 0.1f;
	up.loop = false;
	up.pingpong = true;

	down.PushBack({ 48, 36, 15, 15 });
	down.PushBack({ 64, 36, 15, 15 });
	down.PushBack({ 80, 36, 15, 15 });
	down.speed = 0.1f;
	down.loop = false;
	down.pingpong = true;


	rigth.PushBack({ 95, 36, 15, 15 });
	rigth.PushBack({ 111, 36, 15, 15 });
	rigth.PushBack({ 127, 36, 15, 15 });
	rigth.speed = 0.1f;
	rigth.loop = false;
	rigth.pingpong = true;


	left.PushBack({ 0, 36, 15, 15 });
	left.PushBack({ 15, 36, 15, 15 });
	left.PushBack({ 31, 36, 15, 15 });
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


	//timer++;
	//if (timer > 40)
	//{
	//	changeTimer++;
	//}


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


	if (changeTimer >= 80)
	{
		changeLimit = false;
		changeTimer = 0;
	}

	//App->player->Update();
	if (App->player->devourer == true) currentMode = CHASE;
	if (App->player->devourer == false) currentMode = FEAR;


	//if (changeTimer >= 80)
	//{
	//	changeLimit = false;
	//	changeTimer = 0;
	//}

	switch (currentMode)
	{

	case GhostBlinky::CHASE:

		up1.PushBack({ 144, 69, 15, 15 });
		up1.PushBack({ 160, 69, 15, 15 });
		up1.PushBack({ 176, 69, 15, 15 });
		up1.loop = true;
		up1.speed = 0.05f;

		down1.PushBack({ 48, 69, 15, 15 });
		down1.PushBack({ 64, 69, 15, 15 });
		down1.PushBack({ 80, 69, 15, 15 });
		down1.loop = true;
		down1.speed = 0.05f;

		rigth1.PushBack({ 95, 69, 15, 15 });
		rigth1.PushBack({ 111, 69, 15, 15 });
		rigth1.PushBack({ 127, 69, 15, 15 });
		rigth1.loop = true;
		rigth1.speed = 0.05f;

		left1.PushBack({ 0, 69, 15, 15 });
		left1.PushBack({ 15, 69, 15, 15 });
		left1.PushBack({ 31, 69, 15, 15 });
		left1.loop = true;
		left1.speed = 0.05f;

		Movementspeed = 0.6f;

		//NIVEL 1
		switch (currentDirection) //NIVEL 1
		{

		case GhostBlinky::UP:
		{
			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y -= Movementspeed;
				currentAnim = &up1;
			}
			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;
				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					LOG("No cambio");
					//Continue going
					break;
				case(1):
					LOG("Cambio");
					currentDirection = LEFT;
					break;
				}
			}

			if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->EMPTY && (int)position.x % 8 == 0
				&& (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
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
				if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;
				}
				//Pared Derecha--> Izquierda
				if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;
				}
			}

			break;
		}


		case GhostBlinky::LEFT:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
			{
				position.x -= Movementspeed;
				currentAnim = &left1;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
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
				if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;
				}
				//Pared bajo--> Alta
				if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = UP;
				}
			}
			break;
		}


		case GhostBlinky::DOWN:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y += Movementspeed;
				currentAnim = &down1;

			}

			//CAMBIAR DIRECCION EN UN CRUCE


			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
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
				if (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}
			break;
		}

		case GhostBlinky::RIGTH:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
			{
				position.x += Movementspeed;
				currentAnim = &rigth1;
			}


			//CAMBIAR DIRECCION EN UN CRUCE



			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
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
				if (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared abajo--> Sube
				if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}
			}
			break;
		}



		default:
			break;
		} //NIVEL 4 //NIVEL
		//NIVEL 4
		switch (currentDirection) 
		{

		case GhostBlinky::UP:
		{
			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] >= App->sceneLevel_4->GHOST)
			{
				position.y -= Movementspeed;
				currentAnim = &up1;
			}
			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;
				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					LOG("No cambio");
					//Continue going
					break;
				case(1):
					LOG("Cambio");
					currentDirection = LEFT;
					break;
				}
			}

			if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->EMPTY && (int)position.x % 8 == 0
				&& (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
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
				if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;
				}
				//Pared Derecha--> Izquierda
				if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;
				}
			}

			break;
		}


		case GhostBlinky::LEFT:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->GHOST ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 2] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 2] == App->sceneLevel_4->TP))
			{
				position.x -= Movementspeed;
				currentAnim = &left1;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && (int)position.x % 8 == 0)
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
				if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;
				}
				//Pared bajo--> Alta
				if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = UP;
				}
			}
			break;
		}


		case GhostBlinky::DOWN:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] >= App->sceneLevel_4->GHOST)
			{
				position.y += Movementspeed;
				currentAnim = &down1;

			}

			//CAMBIAR DIRECCION EN UN CRUCE


			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
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
				if (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}
			break;
		}

		case GhostBlinky::RIGTH:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->GHOST ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y - 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y - 1] == App->sceneLevel_4->TP))
			{
				position.x += Movementspeed;
				currentAnim = &rigth1;
			}


			//CAMBIAR DIRECCION EN UN CRUCE



			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL) && (int)position.x % 8 == 0)
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
				if (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared abajo--> Sube
				if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
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
	case GhostBlinky::SCATTER:
		break;
	case GhostBlinky::FEAR:
		
		//NIVEL 1
		switch (currentDirection)
		{

		case GhostBlinky::UP:
		{
			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y -= Movementspeed;
				currentAnim = &up;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;

				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					LOG("No cambio");
					//Continue going
					break;
				case(1):
					LOG("Cambio");
					currentDirection = LEFT;
					break;
				}
			}

			if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->EMPTY && (int)position.x % 8 == 0
				&& (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
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
				if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}

			break;
		}


		case GhostBlinky::LEFT:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 2] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 2] == App->sceneLevel_1->TP))
			{
				position.x -= Movementspeed;
				currentAnim = &left;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->EMPTY && App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
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
				if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared bajo--> Alta
				if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}

			}
			break;
		}


		case GhostBlinky::DOWN:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] >= App->sceneLevel_1->GHOST)
			{
				position.y += Movementspeed;
				currentAnim = &down;

			}

			//CAMBIAR DIRECCION EN UN CRUCE


			if ((App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileRight.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
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
				if (App->sceneLevel_1->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}
			break;
		}

		case GhostBlinky::RIGTH:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_1->GHOST ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_1->TP) ||
				(App->sceneLevel_1->TileSet[level][tile.x][tile.y - 1] == App->sceneLevel_1->TP && App->sceneLevel_1->TileSet[level][tile.x + 1][tile.y - 1] == App->sceneLevel_1->TP))
			{
				position.x += Movementspeed;
				currentAnim = &rigth;
			}


			//CAMBIAR DIRECCION EN UN CRUCE



			if ((App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_1->GHOST && App->sceneLevel_1->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_1->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_1->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_1->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_1->WALL) && (int)position.x % 8 == 0)
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
				if (App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared abajo--> Sube
				if (App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_1->WALL || App->sceneLevel_1->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_1->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}
			}
			break;
		}



		default:
			break;
		}
		//NIVEL 2
		switch (currentDirection)
		{

		case GhostBlinky::UP:
		{
			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] >= App->sceneLevel_4->GHOST)
			{
				position.y -= Movementspeed;
				currentAnim = &up;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
			{
				changeLimit = true;
				changeTimer = 0;

				newDir = rand() % 2;
				switch (newDir)
				{
				case(0):
					LOG("No cambio");
					//Continue going
					break;
				case(1):
					LOG("Cambio");
					currentDirection = LEFT;
					break;
				}
			}

			if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->EMPTY && (int)position.x % 8 == 0
				&& (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
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
				if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}

			break;
		}


		case GhostBlinky::LEFT:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->GHOST ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 2] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 2] == App->sceneLevel_4->TP))
			{
				position.x -= Movementspeed;
				currentAnim = &left;
			}

			//CAMBIAR DIRECCION EN UN CRUCE
			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->EMPTY && App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_4->EMPTY)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL) && (int)position.x % 8 == 0)
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
				if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared bajo--> Alta
				if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL) && (int)position.y % 8 == 0)
				{
					currentDirection = UP;

				}

			}
			break;
		}


		case GhostBlinky::DOWN:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] >= App->sceneLevel_4->GHOST)
			{
				position.y += Movementspeed;
				currentAnim = &down;

			}

			//CAMBIAR DIRECCION EN UN CRUCE


			if ((App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileRight.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
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
				if (App->sceneLevel_4->TileSet[level][tileLeft.x][tileLeft.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileLeft.x + 1][tileLeft.y] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = RIGTH;

				}
				//Pared Derecha--> Izquierda
				if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = LEFT;

				}


			}
			break;
		}

		case GhostBlinky::RIGTH:
		{

			//SEGUIR ADELANTE SI NO HAY PARED
			if (App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] >= App->sceneLevel_4->GHOST ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y + 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y + 1] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y] == App->sceneLevel_4->TP) ||
				(App->sceneLevel_4->TileSet[level][tile.x][tile.y - 1] == App->sceneLevel_4->TP && App->sceneLevel_4->TileSet[level][tile.x + 1][tile.y - 1] == App->sceneLevel_4->TP))
			{
				position.x += Movementspeed;
				currentAnim = &rigth;
			}


			//CAMBIAR DIRECCION EN UN CRUCE



			if ((App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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

			if ((App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] >= App->sceneLevel_4->GHOST && App->sceneLevel_4->TileSet[level][tileDown.x + 1][tileDown.y] >= App->sceneLevel_4->GHOST)
				&& ((int)position.x % 8 == 0 && (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x + 1][tileUp.y] == App->sceneLevel_4->WALL)) && changeLimit == false)
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
			if ((App->sceneLevel_4->TileSet[level][tileRight.x][tileRight.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileRight.x + 1][tileRight.y] == App->sceneLevel_4->WALL) && (int)position.x % 8 == 0)
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
				if (App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileUp.x][tileUp.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
				{
					currentDirection = DOWN;

				}
				//Pared abajo--> Sube
				if (App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y] == App->sceneLevel_4->WALL || App->sceneLevel_4->TileSet[level][tileDown.x][tileDown.y + 1] == App->sceneLevel_4->WALL && (int)position.y % 8 == 0)
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


