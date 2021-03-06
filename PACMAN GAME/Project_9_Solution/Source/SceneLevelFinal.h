#ifndef __SCENE_LEVELFINAL_H__
#define __SCENE_LEVELFINAL_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevelFinal : public Module
{
public:
	//Constructor
	SceneLevelFinal(bool startEnabled);

	//Destructor
	~SceneLevelFinal();

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
	int position_clear_x = -75;
	int position_clear_x2 = 100;
	int position_clear_y = 350;

	bool victory = false;

	uint clear = 0;
	uint round = 0;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int scoreFont2 = -1;
	char scoreText2[10] = { "\0" };

	SDL_Rect world1 = { 207, 95, 48, 16 };
	SDL_Rect p1 = { 0, 96, 8, 16 };
	SDL_Rect p2 = { 0, 112, 8, 16 };


	enum TypesOfTiles
	{
		WALL,
		GHOST,
		EMPTY,
		TP,
		DASH,

		MAX_TYPES
	};

	uint round1 = 0;

	//TileSet del nivel
	const int TileX = 31;
	const int TileY = 39;

	//[3d la profundidad][la altura] [la longuitud] 
	int TileSet[2][39][31] = {
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY  ,  //0 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY  ,	//1 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY  , 	//2 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY  ,	//3 *
	 EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY  ,	//4 *
	 EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY  ,	//5 *
	 EMPTY ,EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY   ,   //6 *
	 EMPTY ,WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, EMPTY   ,	//7 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, WALL,EMPTY   ,	//8 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//9 *
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL, EMPTY, EMPTY, WALL,EMPTY   ,	//10 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//11 *
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//12 *
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL, EMPTY, EMPTY, WALL,EMPTY   ,	//13*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL, EMPTY, EMPTY, WALL,EMPTY   ,	//14 *
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//15 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//16 *
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY   , 	//17 *
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL, EMPTY, EMPTY,WALL,EMPTY   ,	//18 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,  EMPTY,WALL,EMPTY   ,	//19 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,  EMPTY,WALL,EMPTY   ,	//20*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL ,EMPTY, EMPTY,WALL,EMPTY   ,	//21 *
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//22 *
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//23*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY   ,	//24*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY   ,	//25*
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//26*
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//27*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY   ,	//28*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY   ,	//29*
	 EMPTY ,WALL,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//31*
	 EMPTY ,WALL,EMPTY,EMPTY, EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//32*
	 EMPTY ,WALL,EMPTY,EMPTY, WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL,WALL,EMPTY,EMPTY,WALL, EMPTY, EMPTY,WALL,EMPTY   ,	//33*
	 EMPTY ,WALL,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY   ,	//34*
	 EMPTY ,WALL, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,EMPTY ,	//35*
	 EMPTY ,WALL,WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,WALL,WALL,WALL,EMPTY   ,		//36*
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,
	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,	//37*
	// 0      1      2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28   29   30

	 EMPTY ,EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY ,
	};
};

#endif