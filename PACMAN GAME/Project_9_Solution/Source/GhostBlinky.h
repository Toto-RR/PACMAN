#pragma once

//GHOST BLINKY CODE

#ifndef __GHOST_BLINKY_H__
#define __GHOST_BLINKY_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

class GhostBlinky : public Enemy {
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	GhostBlinky(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int currentDirection;
	int newDir;

	int changeTimer = 10;
	bool changeLimit;

	enum DIRECTIONS
	{
		UP,
		LEFT,
		DOWN,
		RIGTH,
	};

	enum MODES {
		CHASE,
		SCATTER,
		FEAR,
		EATEN,
	};

	bool Eatable = false;

	int currentMode;

	float movSpeed = 0.8f;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation up, down, left, rigth;

	iPoint tile, tileUp, tileDown, tileLeft, tileRight;

	fPoint objectives;

	int timer = 0;

};


#endif
