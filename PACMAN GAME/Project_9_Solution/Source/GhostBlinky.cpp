#include "GhostBlinky.h"

#include "Application.h"
#include "ModuleCollisions.h"

GhostBlinky::GhostBlinky(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 159, 17, 15, 15 });
	up.PushBack({ 159, 18, 15, 15 });
	currentAnim = &up;
	up.speed = 0.05f;
	up.loop = true;

	down.PushBack({ 64, 17, 15, 15 });
	down.PushBack({ 64, 18, 15, 15 });
	currentAnim = &down;
	down.speed = 0.05f;
	down.loop = true;


	right.PushBack({ 111, 17, 15, 15 });
	right.PushBack({ 111, 18, 15, 15 });
	currentAnim = &right;
	right.speed = 0.05f;
	right.loop = true;

	left.PushBack({ 15, 17, 15, 15 });
	left.PushBack({ 15, 18, 15, 15 });
	currentAnim = &left;
	left.speed = 0.05f;
	left.loop = true;

	path.PushBack({ -0.5f, 0.0f }, 142, &left);
	/*path.PushBack({ 0.0f, 0.5f }, 205, &down);
	path.PushBack({ 0.5f, 0.0f }, 32, &right);
	path.PushBack({ 0.0f, 0.5f }, 32, &down);
	path.PushBack({ 0.5f, 0.0f }, 48, &right);
	path.PushBack({ 0.0f, -0.5f }, 32, &up);
	path.PushBack({ 0.5f, 0.0f }, 144, &right);
	path.PushBack({ 0.0f, 0.5f }, 32, &down);
	path.PushBack({ 0.5f, 0.0f }, 42, &right);
	path.PushBack({ 0.0f, 0.5f }, 48, &down);
	path.PushBack({ 0.5f, 0.0f }, 48, &right);
	path.PushBack({ 0.0f, -0.5f }, 32, &up);
	path.PushBack({ 0.5f, 0.0f }, 32, &right);
	path.PushBack({ 0.0f, -0.5f }, 48, &up);
	path.PushBack({ -0.5f, 0.0f }, 48, &left);
	path.PushBack({ 0.0f, -0.5f }, 48, &up);
	path.PushBack({ -0.5f, 0.0f }, 80, &left);
	path.PushBack({ 0.0f, -0.5f }, 156, &up);
	path.PushBack({ -0.5f, 0.0f }, 78, &left);*/

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}



void GhostBlinky::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}

void GhostBlinky::OnCollision(Collider* c1, Collider* c2) 
{
	if (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::WALL)
	{
		path.PushBack({ 0.1f, 0.0f }, 150, &right);
	}
	
}


