#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "GhostBlinky.h"
#include "GhostClyde.h"
#include "GhostInky.h"
#include "GhostPinky.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = false;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	
}

void Enemy::OnCollision(Collider* collider)
{
	
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}