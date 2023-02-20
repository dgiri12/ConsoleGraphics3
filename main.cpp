//ConsoleGraphics8
//Done-> putting all variables inside instances, the main program accessed these variables using methods.

#include"main.h"

int main()
{
	srand(time(NULL));
	//Startup Routine
	HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	int dummy = _setmode(_fileno(stdout), _O_U16TEXT);//set unicode mode
	CONSOLE_CURSOR_INFO	cursorInfo = { 1,FALSE };
	SetConsoleCursorInfo(myHandle, &cursorInfo);
	screen = cg4.getScreen();
	SetConsoleScreenBufferSize(myHandle, { screen->screenWidth,screen->screenHeight });
	cg4.gameStart(&myHandle,&hwnd); //game starts here
	cg4.flipFpsSwitch(true); 

	//Execute onCreate() routines for each instance, this function helps to set initial values for instances, for example to
	//set initial vertical or horizontal speed.
	for (int i = 0; i < cg4.getInstanceArraySize(); i++)
	{
		Instance* current = cg4.getInstance(i);
		if (current->isNull()) continue; //skip null instances
		onInstanceCreateApplyAction(current->getActionIndex(), i);
	}


	while (1)//main game loop still happens in the main program
	{
		gameUpdate();
	}
	return 0;
}

void gameUpdate()
{
	//Set for keyboard events.
//lower and upper case have different ascii values, but both values work for this
	cg4.setEvent(evVK_W, GetKeyState(87) < 0); //W//if GetKeyState<0 = true, it is pressed.
	cg4.setEvent(evVK_A, GetKeyState(65) < 0);//A
	cg4.setEvent(evVK_S, GetKeyState(83) < 0);//S
	cg4.setEvent(evVK_D, GetKeyState(68) < 0);//D
	cg4.setEvent(evVK_SPACE, GetKeyState(32) < 0);//space
	cg4.setEvent(evVK_E, GetKeyState(69) < 0);// E=69
	
	if (cg4.checkEvent(evVK_E) && enemyRespawning==false) {
		cg4.getTimer(enemyRespawnTimer)->resetTime();
		enemyRespawning = true;
	}
	if (enemyRespawning == true)
	{
		if (cg4.getTimer(enemyRespawnTimer)->getElapsedTime() > 1000) {
			int temp = cg4.addInstance(sprSpaceship, acSpaceship2, rand() % (roomWidth - 10) + 10,
				rand() % (roomHeight - 20) + 10, 0);
			onInstanceCreateApplyAction(acSpaceship2, temp);
			enemyRespawning = false;
		}
	}
	if (playerDestroyed == true)
	{
		if (cg4.getTimer(playerResetTimer)->getElapsedTime() > 1000)
		{
			int objSpaceship = cg4.addInstance(sprSpaceship, acSpaceship, 30, 30, 0);
			onInstanceCreateApplyAction(acSpaceship, objSpaceship);
			playerDestroyed = false;
		}
	}


	//Iterate through the instances inside the game engine
	//and update it

	for (int i = 0; i < cg4.getInstanceArraySize(); i++)
	{
		Instance *instance=cg4.getInstance(i);
		if (instance->isNull()) continue; //skip null instances
		ongoingInstanceApplyAction(instance->getActionIndex(), i);
	}
	
	cg4.gameRender();
}

void onInstanceCreateApplyAction(int _actionIndex, int _instanceIndex)
{
	Instance* current = cg4.getInstance(_instanceIndex);

	switch (_actionIndex) //Never forget the break keyword after a case statement!!
	{
	case acSpaceship:
		charge = current->addVariableInt("charge", 0);
		speed = current->addVariableInt("speed", 1);
		activate = current->addVariableBool("activate", false);
		canShoot = current->addVariableBool("canShoot", true);
		inBulletTimer = current->addVariableInt("inBulletTimer", cg4.addTimer()); //this is a local timer
		break;
	case acSpaceship2:
		//Choose an initial VSpeed of up or down direction besides zero
		/*while (current->getVSpeed() == 0)
		{
			int vs = rand() % 2 + 1;
			if (vs == 1) current->setVSpeed(1);
			if (vs == 2) current->setVSpeed(-1);
		}*/
		while (current->getHSpeed() == 0)
		{
			int hs = rand() % 2 + 1;
			if (hs == 1) current->setHSpeed(1);
			if (hs == 2) current->setHSpeed(-1);
		}
		break;
	case acBullet:
		current->setVSpeed(-2); //set initial speed for bullet
		break;
	default:
		break;
	}
}
void ongoingInstanceApplyAction(int _actionIndex, int _instanceIndex)
{
	Instance* current = cg4.getInstance(_instanceIndex);
	Timer* bulletTimer;

	switch (_actionIndex) //Never forget the break keyword after a case statement!!
	{
	case acSpaceship:
		current->setHSpeed(0);
		current->setVSpeed(0);
		bulletTimer = cg4.getTimer(current->getVariableIntValue(inBulletTimer));
		//Make appropriate sprite changes
		if (current->getVariableIntValue(charge) == 0) current->setSpriteIndex(sprSpaceship);
		if (current->getVariableIntValue(charge) > 40) current->setSpriteIndex(sprSpaceshipCharging);
		if (current->getVariableIntValue(charge) >= 100) current->setSpriteIndex(sprSpaceshipFullyCharged);

		current->setVariableBoolValue(activate, true);
		//current->setVariableBoolValue(canShoot);
		if (current->getVariableBoolValue(activate)) {
			if (cg4.checkEvent(evVK_A)) current->setHSpeed(-current->getVariableIntValue(speed));
			if (cg4.checkEvent(evVK_W)) current->setVSpeed(-current->getVariableIntValue(speed));
			if (cg4.checkEvent(evVK_S)) current->setVSpeed(current->getVariableIntValue(speed));
			if (cg4.checkEvent(evVK_D))	current->setHSpeed(current->getVariableIntValue(speed));
		}
		if (cg4.checkEvent(evVK_SPACE)) {
			if (current->getVariableIntValue(charge) < 100)current->setVariableIntValue(charge, current->getVariableIntValue(charge) + 1);
			if (current->getVariableBoolValue(canShoot) == true) {
				int temp = cg4.addInstance(sprBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp); //call this 2nd function each time you create an instance,
				//because the "on creation" needs to be called for a new instance, this is what helps set the initial VSpeed of a 
				//bullet even though it was created in the middle of the game
				current = cg4.getInstance(_instanceIndex); //reupdating the current pointer because "addInstance" method changes the array structure,
				//and we end up losing the address that current pointed to, so obviously none of the variable operations would work after that.
				//update current pointer each time a new instance is created. This is not required outsideof the applyAction function.
				bulletTimer->resetTime();
				current->setVariableBoolValue(canShoot, false);
			}
		}
		if (current->getVariableBoolValue(canShoot) == false && !cg4.checkEvent(evVK_SPACE))
		{
			if (bulletTimer->getElapsedTime() >= 250)
			{
				current->setVariableBoolValue(canShoot, true);
			}
		}
		if (!cg4.checkEvent(evVK_SPACE))
		{
			if (current->getVariableIntValue(charge) >= 100)
			{
				int temp = cg4.addInstance(sprFullChargeBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp);
				current = cg4.getInstance(_instanceIndex);
				current->setVariableIntValue(charge, 0);
				break;
			}
			if (current->getVariableIntValue(charge) > 40)
			{
				int temp = cg4.addInstance(sprChargeBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp);
				current = cg4.getInstance(_instanceIndex);
				current->setVariableIntValue(charge, 0);
				break;
			}
		}
		if (cg4.checkCollision(_instanceIndex, objSpaceship2))
		{
			int temp = cg4.addInstance(sprExplosion, acExplosion, current->getX(), current->getY(), 0);
			current = cg4.getInstance(_instanceIndex);
			cg4.destroyInstance(_instanceIndex);
			cg4.getTimer(playerResetTimer)->resetTime();
			playerDestroyed = true;

		}
		break;
	case acBullet:
		if (current->getY() < 0) cg4.destroyInstance(_instanceIndex);

		if (cg4.checkCollision(_instanceIndex, objSpaceship2))
		{
			cg4.destroyInstance(_instanceIndex);
			int temp = cg4.addInstance(sprExplosion, acExplosion,
				cg4.getInstance(objSpaceship2)->getX(),
				cg4.getInstance(objSpaceship2)->getY(), 0);
			//NOT NEEDED just for ref->current = cg4.getInstance(_instanceIndex);
			//current needs to be reset when new instances are added,
			//but when both objects are destroyed, current need not be updated. Also, keep instance destruction at
			//the end of the action, always, or some portion of code won't be executed.
			cg4.destroyInstance(objSpaceship2);
		}
		break;
	case acSpaceship2:
		//Flip direction when spaceship goes outside screen
		if (current->getX() > roomWidth - cg4.getSprite(current->getSpriteIndex())->getSprOriginX()) {
			current->setHSpeed(-current->getHSpeed());
		}
		if (current->getX() < cg4.getSprite(current->getSpriteIndex())->getSprOriginX()) current->setHSpeed(-current->getHSpeed());

		if (current->getY() > roomHeight - cg4.getSprite(current->getSpriteIndex())->getSprOriginY()) current->setVSpeed(-current->getVSpeed());
		if (current->getY() < cg4.getSprite(current->getSpriteIndex())->getSprOriginY()) current->setVSpeed(-current->getVSpeed());
		break;
	case acExplosion:
		if (current->checkInsEvent(evInsENDOFANIMATION)) cg4.destroyInstance(_instanceIndex);
		break;
	default:
		break; //no break statement needed because 'return' acts as break
	}
	//These ending statements are supposed to globally changes for all actionIndices, for example, hspeed and vspeed needs to always
	//be processed.
	current->setX(current->getX() + current->getHSpeed());
	current->setY(current->getY() + current->getVSpeed());
}
