#include "GhostBlinky.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostBlinky::GhostBlinky(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 159, 17, 15, 15 });
	currentAnim = &up;

	down.PushBack({ 64, 17, 15, 15 });
	currentAnim = &down;

	right.PushBack({ 111, 17, 15, 15 });
	currentAnim = &right;

	left.PushBack({ 15, 17, 15, 15 });
	currentAnim = &left;

	path.PushBack({ 0.1f, 0.0f }, 150, &right);

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void GhostBlinky::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}

void GhostBlinky::OnCollision(Collider* collider) 
{
	if (this->collider->ENEMY && collider->WALL) 
	{
		path.PushBack({ 0.0f, -0.1f }, 150, &down);
	}
	
}

