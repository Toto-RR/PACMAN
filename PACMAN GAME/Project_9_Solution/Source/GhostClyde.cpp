#include "GhostClyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostClyde::GhostClyde(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 0, 0, 18, 18 });
	currentAnim = &up;

	down.PushBack({ 0, 0, 18, 18 });
	currentAnim = &down;

	right.PushBack({ 0, 0, 18, 18 });
	currentAnim = &right;

	left.PushBack({ 0, 0, 18, 18 });
	currentAnim = &left;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void GhostClyde::Update()
{
	

	Enemy::Update();
}