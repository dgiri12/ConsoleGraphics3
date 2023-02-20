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
ActionVariables applyAction(int _actionIndex, ActionVariables _actionVariables, int _instanceIndex);
void gameUpdate();

//Sprites
int sprStartScreen=cg4.addSprite("sprites/splashScreen1.txt");
int sprGamePlayScreen = cg4.addSprite("sprites/gameplayScreen.txt");
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

struct stSpaceship //st->struct
{
	int inBulletTimer = cg4.addTimer();
	bool canShoot = true;
	int charge = 0;
	int objSpaceshipIndex = cg4.addInstance(sprSpaceship, acSpaceship, 30, 30, 0);
}; stSpaceship objSpaceship; //create only one instance of this struct, i am only doing this to group the variable for each instance

//uservariableint test
Instance* temp = cg4.getInstance(objSpaceship.objSpaceshipIndex);
int speed = temp->addUserVariableInt("speed", 1);
int activate = temp->addUserVariableBool("activate", false);

