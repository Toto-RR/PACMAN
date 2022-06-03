#include "GhostClyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

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

	right.PushBack({ 111, 0, 15, 15 });
	right.PushBack({ 111, 1, 15, 15 });
	currentAnim = &right;
	right.loop = true;
	right.speed = 0.05f;

	left.PushBack({ 16, 0, 15, 15 });
	left.PushBack({ 16, 1, 15, 15 });
	currentAnim = &left;
	left.loop = true;
	left.speed = 0.05f;

	path.PushBack({ 0.5f, 0.0f }, 130, &right);
	path.PushBack({ 0.0f, 0.5f }, 208, &down);
	path.PushBack({ -0.5f, 0.0f }, 32, &left);
	path.PushBack({ 0.0f, 0.5f }, 32, &down);
	path.PushBack({ -0.5f, 0.0f }, 48, &left);
	path.PushBack({ 0.0f, -0.5f }, 32, &up);
	path.PushBack({ -0.5f, 0.0f }, 94, &left);
	path.PushBack({ 0.0f, -0.5f }, 48, &up);
	path.PushBack({ -0.5f, 0.0f }, 48, &left);
	path.PushBack({ 0.0f, -0.5f }, 159, &up);
	path.PushBack({ 0.5f, 0.0f }, 94, &right);
	
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