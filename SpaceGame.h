#pragma once
#include"ConsoleGraphics3.h"

//Define action indices
#define acNone -1
#define acSpaceship 0
#define acBullet 1
#define acSpaceship2 2
#define acExplosion 3

//Global variables and objects
class SpaceGame : public ConsoleGraphics3
{
protected:
	//Initialize instances and their indices

	int sprStartScreen = addSprite("sprites/splashScreen1.txt");
	int sprGamePlayScreen = addSprite("sprites/gameplayScreen.txt");
	//set roomWidth and roomHeight variables depending on this sprite's dimensions.
	int roomWidth = getSprite(sprGamePlayScreen)->getSprWidth();
	int roomHeight = getSprite(sprGamePlayScreen)->getSprHeight() - 5;


	int sprSaturn = addSprite("sprites/saturn.txt");
	int sprSpaceship = addSprite("sprites/spaceship.txt");
	int sprSpaceshipCharging = addSprite("sprites/spaceshipCharging.txt");
	int sprSpaceshipFullyCharged = addSprite("sprites/spaceshipFullyCharged.txt");
	int sprBullet = addSprite("sprites/bullet.txt");
	int sprChargeBullet = addSprite("sprites/chargeBullet.txt");
	int sprFullChargeBullet = addSprite("sprites/fullChargeBullet.txt");
	int sprExplosion = addSprite("sprites/explosion.txt");

	//Initialize instances and their indices
	int objGamePlayScreen = addInstance(sprGamePlayScreen, acNone, 0, 0, 0);
	int objSaturn = addInstance(sprSaturn, acNone, 91, 16, 0);
	int objSpaceship2 = addInstance(sprSpaceship, acSpaceship2, 40, 7, 0);

	//Initialization of the main player------------------------
	int objSpaceship = addInstance(sprSpaceship, acSpaceship, 30, 30, 0);
	//Some variable used for influencing actions of this instance
	int charge=0, speed=0, activate=0, canShoot=0, inBulletTimer=0;
	//---------------------------------------------------------------

	//Some timers
	//depending on where timers are used, it can be local to an instance or global across the main game
//declare timerIndex outside like this to access this timer throughout the game.
	int playerResetTimer = addTimer();
	bool playerDestroyed = false;//activate this timer when player gets destroyed, 
	//then during the game loop wait for this timer to go off and create player instance.

	//timer to respawn an enemy after user presses a button
	int enemyRespawnTimer = addTimer();
	bool enemyRespawning = false;
	bool timeToRespawn = true;
	//Constructors
	//Overloaded virtual functions
	void onInstanceCreateApplyAction(int _actionIndex, int _instanceIndex);
	
	void ongoingInstanceApplyAction(int _actionIndex, int _instanceIndex);
public:
	SpaceGame();

	void gameUpdate();
};
