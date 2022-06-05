#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Items.png");

	// Particles
	SuperPacdotAnim.anim.PushBack({ 0, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 0, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 0, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 16, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 33, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 49, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 64, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 49, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 33, 0, 8, 8 });
	SuperPacdotAnim.anim.PushBack({ 16, 0, 8, 8 });
	SuperPacdotAnim.anim.loop = true;
	SuperPacdotAnim.anim.speed = 0.06f;

	PacdotAnim.anim.PushBack({ 0, 11, 5, 15});
	PacdotAnim.anim.PushBack({ 7, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 15, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 22, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 29, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 37, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 44, 11, 5, 15 });
	PacdotAnim.anim.PushBack({ 51, 11, 5, 15 });
	PacdotAnim.anim.loop = true;
	PacdotAnim.anim.speed = 0.06f;

	PineappleAnim.anim.PushBack({ 0, 28, 17, 17 });
	PineappleAnim.anim.PushBack({ 0, 29, 17, 17 });
	PineappleAnim.anim.pingpong = true;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	--COUNTDOWN;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleParticles::AddPacdot(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	++COUNTDOWN;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}
void ModuleParticles::AddSuperpacdot(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	++COUNTDOWN;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}

