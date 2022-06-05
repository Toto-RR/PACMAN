#pragma once

//GHOST BLINKY CODE

#ifndef __GHOST_BLINKY_H__
#define __GHOST_BLINKY_H__

#include "Enemy.h"
#include "Path.h"


class GhostBlinky : public Enemy {
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	GhostBlinky(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;


	//Scene
	int scene;


	enum DIRECTIONS
	{
		UP,
		LEFT,
		DOWN,
		RIGTH,
	};

	int currentDirection;
	int newDir;
	//Ghost cannot change direction in an intersection if it didn't underwent the opposite direction
	int changeTimer = 10;
	bool changeLimit;


	//GHOST MODES
	enum MODES
	{
		CHASE,
		SCATTER,
		FEAR,
		EATEN,
	};

	int currentMode;

	//Movement speed
	float Movementspeed = 0.8f;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation up; //TODO
	Animation down;
	Animation rigth;
	Animation left;


	//Tile Movement
	iPoint tile;
	iPoint tileUp;
	iPoint tileDown;
	iPoint tileLeft;
	iPoint tileRight;

	//Where the ghost tries to go
	fPoint objectives;

	int level;
	int timer = 0;
};

#endif 
