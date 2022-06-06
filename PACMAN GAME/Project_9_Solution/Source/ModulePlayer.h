#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

//ESCENAS/NIVELES
#include "SceneLevel1.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void RemovePacman(Collider* collider);

public:
	// Position of the player in the map
	fPoint position;

	// Position of packman in the TileSet ERIC

	iPoint tile;

	//Tiles that Pac-Man can move to
	iPoint tileUp;
	iPoint tileDown;
	iPoint tileLeft;
	iPoint tileRight;

	//MAX I POSITION=29 (0-28))
	//MAX I POSITION=38 (0-37))


	// The speed in which we move the player (pixels per frame)
	float speed = 0.8; //ERIC: Cambiada la velocidad a la que se mueve PacMam 

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations TODO: Ampliar
	Animation idleAnim; //Animación de inicio, luego no vuelve a usarse

	Animation upAnim;  //Animaciones ciclicas (.loop=true)
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;

	//MOVERSE EN ESA DIRECCION
	bool MovingUp = false;
	bool MovingDown = false;
	bool MovingLeft = false;
	bool MovingRight = false;


	Animation death; //Animacion de muerte

	// The player's collider
	Collider* collider = nullptr;
	Collider* POSICIONTILE = nullptr; //ERIC: PARA EL DEBUGGGING DE DETECCION DE TILE

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint explosionFx = 0;
	uint Superpacdot = 0;
	uint Pacdot = 0;

	Uint32 start;
	Uint32 stop;

	// God mode
	bool godMode = false;
	bool dead = false;
	bool devourer = false;

	//Fonts
	uint score = 000;
	uint highScore = 000;
	int scoreFont = -1;
	int player1Font = -1;
	int player2Font = -1;
	char scoreText[10] = { "\0" };
	char highScoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__
