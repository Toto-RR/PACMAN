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

	path.PushBack({ -1.0f, 0.0f }, 71, &left);
	path.PushBack({ 0.0f, 1.1f }, 86, &down);
	path.PushBack({ 1.0f, 0.0f }, 16, &right);
	path.PushBack({ 0.0f, 1.0f }, 16, &down);
	path.PushBack({ 1.0f, 0.0f }, 24, &right);
	path.PushBack({ 0.0f, -1.0f }, 16, &up);
	path.PushBack({ 1.0f, 0.0f }, 72, &right);
	path.PushBack({ 0.0f, 1.0f }, 16, &down);
	path.PushBack({ 1.0f, 0.0f }, 16, &right);
	path.PushBack({ 0.0f, 1.0f }, 24, &down);
	path.PushBack({ 1.0f, 0.0f }, 24, &right);
	path.PushBack({ 0.0f, -1.0f }, 16, &up);
	path.PushBack({ 1.0f, 0.0f }, 16, &right);
	path.PushBack({ 0.0f, -1.0f }, 24, &up);
	path.PushBack({ -1.0f, 0.0f }, 24, &left);
	path.PushBack({ 0.0f, -1.0f }, 24, &up);
	path.PushBack({ -1.0f, 0.0f }, 40, &left);
	path.PushBack({ 0.0f, -1.0f }, 80, &up);
	path.PushBack({ -1.0f, 0.0f }, 46, &left);

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
		path.PushBack({ -0.1f, 0.0f }, 150, &left);
		
		GhostBlinky::Update();
		Enemy::Update();
	}
	
}


