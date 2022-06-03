#include "GhostClyde.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostClyde::GhostClyde(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 160, 0, 15, 15 });
	up.PushBack({ 160, 1, 15, 15 });
	currentAnim->loop = true;
	currentAnim->speed = 0.1f;
	currentAnim = &up;
	
	down.PushBack({ 65, 0, 15, 15 });
	down.PushBack({ 65, 1, 15, 15 });
	currentAnim->loop = true;
	currentAnim->speed = 0.1f;
	currentAnim = &down;

	right.PushBack({ 111, 0, 15, 15 });
	down.PushBack({ 65, 1, 15, 15 });
	currentAnim->loop = true;
	currentAnim->speed = 0.1f;
	currentAnim = &right;

	left.PushBack({ 16, 0, 15, 15 });
	down.PushBack({ 65, 1, 15, 15 });
	currentAnim->loop = true;
	currentAnim->speed = 0.1f;
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


void GhostClyde::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}