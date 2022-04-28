//#include "ModuleSuperPacdot.h"
//
//#include "Application.h"
//
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
//#include "ModuleCollisions.h"
//
//
//
//ModuleSuperPacdot::ModuleSuperPacdot(bool startEnabled) : Module(startEnabled)
//{
//	
//}
//
//ModuleSuperPacdot::~ModuleSuperPacdot()
//{
//
//}
//
//bool ModuleSuperPacdot::Start()
//{
//	LOG("Loading SuperPacdots");
//
//	collider = App->collisions->AddCollider({ 0, 0, 14, 13 }, Collider::Type::SUPERPACDOT, (Module*)App->superPacdot);
//
//	texture = App->textures->Load("Assets/Sprites/PowerItem.png");
//
	//SuperPacdotAnim.PushBack({1, 0, 14, 13});
	//SuperPacdotAnim.PushBack({ 16, 0, 14, 13 });
	//SuperPacdotAnim.PushBack({ 31, 0, 14, 13 });
	//SuperPacdotAnim.PushBack({ 45, 0, 14, 13 });
	//SuperPacdotAnim.PushBack({ 57, 0, 14, 13 });
	//&currentAnimation;
	//
	//SuperPacdotAnim.loop = true;
	//SuperPacdotAnim.speed = 0.2f;
//
//	return true;
//}
//
//Update_Status ModuleSuperPacdot::PreUpdate() 
//{
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//bool ModuleSuperPacdot::CleanUp() 
//{
//	
//
//	return true;
//}
//
//void ModuleSuperPacdot::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1->type == Collider::Type::SUPERPACDOT && c2->type == Collider::Type::PLAYER && eated == false)
//	{
//		CleanUp();
//	}
//}
//
//Update_Status ModuleSuperPacdot::Update()
//{
//	for (uint i = 0; i < MAX_ACTIVE_SUPERDOTS; ++i) 
//	{
//		Particle* superdot = superdots[i];
//
//		if (superdot = nullptr) continue;
//
//		if (superdot->Update() == false)
//		{
//			superdots[i]->SetToDelete();
//		}
//	}
//
//	return Update_Status::UPDATE_CONTINUE;
//}
//
//Update_Status ModuleSuperPacdot::PostUpdate()
//{
//	for (uint i = 0; i < MAX_ACTIVE_SUPERDOTS; ++i) {
//
//		Particle* superdot = superdots[i];
//
//		if (superdot != nullptr && superdot->isAlive) {
//			App->render->Blit(texture, superdot->position.x, superdot->position.y, &(superdot->anim.GetCurrentFrame()));
//		}
//	}
//
//	return Update_Status::UPDATE_CONTINUE;
//}