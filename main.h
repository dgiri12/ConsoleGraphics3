#pragma once
#include"ConsoleGraphics3.h"
//Define action indices
#define acNone -1
#define acSpaceship 0
#define acBullet 1
#define acSpaceship2 2
#define acExplosion 3

//Global variables and objects
ConsoleGraphics3 cg4; //Create an instance of the game engine
Screen* screen;

//Function declarations
void gameUpdate();
void onInstanceCreateApplyAction(int _actionIndex, int _instanceIndex);
void ongoingInstanceApplyAction(int _actionIndex, int _instanceIndex);

//Sprites
int sprStartScreen=cg4.addSprite("sprites/splashScreen1.txt");

int sprGamePlayScreen = cg4.addSprite("sprites/gameplayScreen.txt");
//set roomWidth and roomHeight variables depending on this sprite's dimensions.
int roomWidth = cg4.getSprite(sprGamePlayScreen)->getSprWidth();
int roomHeight = cg4.getSprite(sprGamePlayScreen)->getSprHeight()-5;


int sprSaturn=cg4.addSprite("sprites/saturn.txt");
int sprSpaceship=cg4.addSprite("sprites/spaceship.txt");
int sprSpaceshipCharging = cg4.addSprite("sprites/spaceshipCharging.txt");
int sprSpaceshipFullyCharged = cg4.addSprite("sprites/spaceshipFullyCharged.txt");
int sprBullet = cg4.addSprite("sprites/bullet.txt");
int sprChargeBullet = cg4.addSprite("sprites/chargeBullet.txt");
int sprFullChargeBullet = cg4.addSprite("sprites/fullChargeBullet.txt");
int sprExplosion = cg4.addSprite("sprites/explosion.txt");

//Create the instances

int objGamePlayScreen = cg4.addInstance(sprGamePlayScreen, acNone, 0, 0, 0);
int objSaturn = cg4.addInstance(sprSaturn, acNone, 91, 16, 0);
//int objSpaceship = cg4.addInstance(sprSpaceship,acSpaceship, 0, 0, 0);
int objSpaceship2 = cg4.addInstance(sprSpaceship, acSpaceship2, 40, 7, 0);

//Initialization of the main player
int objSpaceship = cg4.addInstance(sprSpaceship, acSpaceship, 30, 30, 0);
//VariableIndex initialization for objSpaceship. Indices are used throughout the game, but variables are local to instances
//Initial data for these local variables are best put within their creation routine, because that way, when these instances are
//created later in the game, these variables can still exist.
int charge, speed, activate, canShoot, inBulletTimer;


//depending on where timers are used, it can be local to an instance or global across the main game
//declare timerIndex outside like this to access this timer throughout the game.
int playerResetTimer = cg4.addTimer();
bool playerDestroyed = false;//activate this timer when player gets destroyed, then during the game loop wait for this timer to
//go off and create player instance.

//timer to respawn an enemy after user presses a button
int enemyRespawnTimer = cg4.addTimer();
bool enemyRespawning = false;


