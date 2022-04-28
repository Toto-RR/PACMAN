#include "GhostClyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostClyde::GhostClyde(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 160, 0, 15, 15 });
	currentAnim = &up;
	down.PushBack({ 65, 0, 15, 15 });
	currentAnim = &down;
	right.PushBack({ 111, 0, 15, 15 });
	currentAnim = &right;
	left.PushBack({ 16, 0, 15, 15 });
	currentAnim = &left;

	path.PushBack({ 1.0f, 0.0f }, 65, &right);
	path.PushBack({ 0.0f, 1.0f }, 105, &down);
	path.PushBack({ -1.0f, 0.0f }, 16, &left);
	path.PushBack({ 0.0f, 1.0f }, 16, &down);
	path.PushBack({ -1.0f, 0.0f }, 23, &left);
	path.PushBack({ 0.0f, -1.0f }, 16, &up);
	path.PushBack({ -1.0f, 0.0f }, 47, &left);
	path.PushBack({ 0.0f, -1.0f }, 24, &up);
	path.PushBack({ -1.0f, 0.0f }, 24, &left);
	path.PushBack({ 0.0f, -1.0f }, 80, &up);
	path.PushBack({ 1.0f, 0.0f }, 47, &right);
	
	path.loop = true;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void GhostClyde::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}