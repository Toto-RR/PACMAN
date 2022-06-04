//#include "ModuleGhosts.h"
//
//#include "Application.h"
//
//#include "ModuleRender.h"
//#include "ModuleTextures.h"
//#include "ModuleAudio.h"
//
//#include "Enemy.h"
//#include "GhostClyde.h"
//#include "GhostBlinky.h"
//#include "GhostInky.h"
//#include "GhostPinky.h"
//
//ModuleGhosts::ModuleGhosts(bool startEnabled) : Module(startEnabled)
//{
//	
//}
//
//ModuleGhosts::~ModuleGhosts() 
//{
//
//}
//
//bool ModuleGhosts::Start()
//{
//	texture = App->textures->Load("Assets/Sprites/Ghosts/enemies.png");
//
//	return true;
//}
//
//Update_Status ModuleGhosts::PreUpdate()
//{
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//Update_Status ModuleGhosts::Update()
//{
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//Update_Status ModuleGhosts::PostUpdate()
//{
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//bool ModuleGhosts::AddEnemy(Enemy_Type type, int x, int y)
//{
//	bool ret = false;
//
//	for (uint i = 0; i < MAX_ENEMIES; ++i)
//	{
//		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
//		{
//			spawnQueue[i].type = type;
//			spawnQueue[i].x = x;
//			spawnQueue[i].y = y;
//			ret = true;
//			break;
//		}
//	}
//
//	return ret;
//
//}