#pragma once

#ifndef __MODULE_SUPERPACDOT_H__
#define __MODULE_SUPERPACDOT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Enemy.h"
#include "Path.h"
#include "Particle.h"

#include "SceneLevel1.h"

#define MAX_ACTIVE_PARTICLES 100

struct Collider;

class ModuleSuperPacdot : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleSuperPacdot(bool startEnabled);

	//Destructor
	~ModuleSuperPacdot();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	Particle SuperPacdotAnim;

	bool eated = false;

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	Particle* particle[MAX_ACTIVE_PARTICLES] = { nullptr };

	

};

#endif // !__MODULE_SUPERPACDOT_H__


