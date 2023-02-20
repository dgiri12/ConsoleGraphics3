#include"SpaceGame.h"

SpaceGame::SpaceGame()
{
	//Execute onCreate routines for each instance, this function helps to set initial values for instances, for example to
//set initial vertical or horizontal speed.
	for (int i = 0; i < instanceArraySize; i++)
	{
		if (getInstance(i)->isNull()) continue; //skip null instances
		onInstanceCreateApplyAction(getInstance(i)->getActionIndex(), i);
	}
}

void SpaceGame::onInstanceCreateApplyAction(int _actionIndex, int _instanceIndex)
{
	Instance* current = getInstance(_instanceIndex);
	switch (_actionIndex) //Never forget the break keyword after a case statement!!
	{
	case acSpaceship:
		charge=0;
		speed=1;
		activate=false;
		canShoot=true;
		inBulletTimer = addTimer(); //this is a local timer
		break;
	case acSpaceship2:
		current->setVSpeed(1);
		break;
	case acBullet:
		current->setVSpeed(-2); //set initial speed for bullet
		break;
	default:
		break;
	}
}
void SpaceGame::gameUpdate()
{
	//Set for keyboard events.
//lower and upper case have different ascii values, but both values work for this
	setEvent(evVK_W, GetKeyState(87) < 0); //W//if GetKeyState<0 = true, it is pressed.
	setEvent(evVK_A, GetKeyState(65) < 0);//A
	setEvent(evVK_S, GetKeyState(83) < 0);//S
	setEvent(evVK_D, GetKeyState(68) < 0);//D
	setEvent(evVK_SPACE, GetKeyState(32) < 0);//space
	//setEvent(evVK_E, GetKeyState(69) < 0);// E=69

	if (timeToRespawn==true && enemyRespawning == false) {
		getTimer(enemyRespawnTimer)->resetTime();
		enemyRespawning = true;
		timeToRespawn = false;
	}
	if (enemyRespawning == true)
	{
		if (getTimer(enemyRespawnTimer)->getElapsedTime() > 1000) {
			int temp = addInstance(sprSpaceship, acSpaceship2, 0, 0, 0);
			Instance* current=getInstance(temp);
			current->setX(rand() % (roomWidth - 15) + 10);
			current->setY(-getSprite(getInstance(temp)->getSpriteIndex())->getSprOriginY());
			onInstanceCreateApplyAction(acSpaceship2, temp);
			enemyRespawning = false;
		}
	}
	if (playerDestroyed == true)
	{
		if (getTimer(playerResetTimer)->getElapsedTime() > 1000)
		{
			objSpaceship = addInstance(sprSpaceship, acSpaceship, 30, 30, 0);
			onInstanceCreateApplyAction(acSpaceship, objSpaceship);
			playerDestroyed = false;
		}
	}

	//Iterate through the instances inside the game engine
	//and update it

	for (int i = 0; i < getInstanceArraySize(); i++)
	{
		Instance* instance = getInstance(i);
		if (instance->isNull()) continue; //skip null instances

		//I chose this place to update local events of instances
		if (getSprite(instance->getSpriteIndex())->getImageIndex()
			== getSprite(instance->getSpriteIndex())->getNoOfImages()-1) {
			instanceArray[i].setInsEvent(evInsENDOFANIMATION, true);
		}
		else
		{
			instanceArray[i].setInsEvent(evInsENDOFANIMATION, false);
		}


		ongoingInstanceApplyAction(instance->getActionIndex(), i);
	}

	gameRender();
}

void SpaceGame::ongoingInstanceApplyAction(int _actionIndex, int _instanceIndex)
{
	Instance* current = getInstance(_instanceIndex);
	Timer* bulletTimer;

	switch (_actionIndex) //Never forget the break keyword after a case statement!!
	{
	case acSpaceship:
		current->setHSpeed(0);
		current->setVSpeed(0);
		bulletTimer = getTimer(inBulletTimer);
		//Make appropriate sprite changes
		if (charge == 0) current->setSpriteIndex(sprSpaceship);
		if (charge > 40) current->setSpriteIndex(sprSpaceshipCharging);
		if (charge >= 100) current->setSpriteIndex(sprSpaceshipFullyCharged);

		activate= true;
		if (activate) {
			if (checkEvent(evVK_A)) current->setHSpeed(-speed);
			if (checkEvent(evVK_W)) current->setVSpeed(-speed);
			if (checkEvent(evVK_S)) current->setVSpeed(speed);
			if (checkEvent(evVK_D))	current->setHSpeed(speed);
		}
		if (checkEvent(evVK_SPACE)) {
			if (charge < 100)charge++;
			if (canShoot == true) {
				int temp = addInstance(sprBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp); //call this 2nd function each time you create an instance,
				//because the "on creation" needs to be called for a new instance, this is what helps set the initial VSpeed of a 
				//bullet even though it was created in the middle of the game
				current = getInstance(_instanceIndex); //reupdating the current pointer because "addInstance" method changes the array structure,
				//and we end up losing the address that current pointed to, so obviously none of the variable operations would work after that.
				//update current pointer each time a new instance is created. This is not required outsideof the applyAction function.
				bulletTimer->resetTime();
				canShoot= false;
			}
		}
		if (canShoot == false && !checkEvent(evVK_SPACE))
		{
			if (bulletTimer->getElapsedTime() >= 250)
			{
				canShoot= true;
			}
		}
		if (!checkEvent(evVK_SPACE))
		{
			if (charge >= 100)
			{
				int temp = addInstance(sprFullChargeBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp);
				current = getInstance(_instanceIndex);
				charge= 0;
				break;
			}
			if (charge > 40)
			{
				int temp = addInstance(sprChargeBullet, acBullet, current->getX(), current->getY(), 0);
				onInstanceCreateApplyAction(acBullet, temp);
				current = getInstance(_instanceIndex);
				charge= 0;
				break;
			}
		}
		if (checkCollision(_instanceIndex, objSpaceship2))
		{
			int temp = addInstance(sprExplosion, acExplosion, current->getX(), current->getY(), 0);
			current = getInstance(_instanceIndex);
			destroyInstance(_instanceIndex);
			getTimer(playerResetTimer)->resetTime();
			playerDestroyed = true;
			timeToRespawn = true;

		}
		break;
	case acBullet:
		if (current->getY() < 0)  destroyInstance(_instanceIndex);

		if (checkCollision(_instanceIndex, objSpaceship2))
		{
			destroyInstance(_instanceIndex);
			int temp = addInstance(sprExplosion, acExplosion,
				getInstance(objSpaceship2)->getX(),
				getInstance(objSpaceship2)->getY(), 0);
			//NOT NEEDED just for ref->current =  getInstance(_instanceIndex);
			//current needs to be reset when new instances are added,
			//but when both objects are destroyed, current need not be updated. Also, keep instance destruction at
			//the end of the action, always, or some portion of code won't be executed.
			destroyInstance(objSpaceship2);
			timeToRespawn = true;
		}
		break;
	case acSpaceship2:
		//Flip direction when spaceship goes outside screen
		if (current->getX() > roomWidth - getSprite(current->getSpriteIndex())->getSprOriginX()) {
			current->setHSpeed(-current->getHSpeed());
		}
		if (current->getX() < getSprite(current->getSpriteIndex())->getSprOriginX()) current->setHSpeed(-current->getHSpeed());

		if (current->getY() > roomHeight - getSprite(current->getSpriteIndex())->getSprOriginY()) {
			destroyInstance(_instanceIndex);
			timeToRespawn = true;
		}
			//current->setVSpeed(-current->getVSpeed());
		//if (current->getY() < getSprite(current->getSpriteIndex())->getSprOriginY()) current->setVSpeed(-current->getVSpeed());
		break;
	case acExplosion:
		if (current->checkInsEvent(evInsENDOFANIMATION))  destroyInstance(_instanceIndex);
		break;
	default:
		break; //no break statement needed because 'return' acts as break
	}
	//These ending statements are supposed to globally changes for all actionIndices, for example, hspeed and vspeed needs to always
	//be processed.
	current->setX(current->getX() + current->getHSpeed());
	current->setY(current->getY() + current->getVSpeed());
}


