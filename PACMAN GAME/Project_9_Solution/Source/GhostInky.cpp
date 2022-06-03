#include "GhostInky.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostInky::GhostInky(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 160, 35, 15, 15 });
	currentAnim = &up;
	down.PushBack({ 65, 35, 15, 15 });
	currentAnim = &down;
	right.PushBack({ 111, 35, 15, 15 });
	currentAnim = &right;
	left.PushBack({ 16, 35, 15, 15 });
	currentAnim = &left;

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


void GhostInky::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}