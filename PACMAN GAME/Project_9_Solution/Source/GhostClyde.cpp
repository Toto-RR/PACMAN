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

	path.PushBack({ -1.0f, 0.0f }, 150, &left);
	/*path.PushBack({ 1.0f, 0.0f }, 150, &right);
	path.PushBack({ 0.0f, 1.0f }, 150, &up);
	path.PushBack({ 0.0f, -1.0f }, 150, &down);*/

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void GhostClyde::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}