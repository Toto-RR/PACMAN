#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* extraTexture = nullptr;
	
	int positionx = 255;
	int positiony = -50;
	int speedx = 5;
	int speedy = 5;

	int position_num_x = -20;
	int position_num_y = 275;
	int speed_num_x = 3;
	int speed_num_y = 3;

	uint round = 0;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int scoreFont2 = -1;
	char scoreText2[10] = { "\0" };

	SDL_Rect world0 = { 63, 98, 46, 14 };
	SDL_Rect p1 = { 0, 96, 8, 16 };
	SDL_Rect p2 = { 0, 112, 8, 16 };
};

#endif