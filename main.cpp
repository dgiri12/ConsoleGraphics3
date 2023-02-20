//ConsoleGraphics6
//add timerArray

#include"main.h"

int main()
{
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

	//Oncreate routine for some instances
	Instance *change = cg4.getInstance(objSpaceship2);
	ActionVariables changeVar = change->getActionVariables();
	changeVar.hspeed = 1;
	change->setActionVariables(changeVar);
	change = nullptr;
	  
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
	//bool toggle = (state & 1) != 0;
	//setEvent(evVK_A, true); //simulate a button press
	//setEvent(evVK_S, true);

	//Iterate through the instances inside the game engine
	//and update it
	for (int i = 0; i < cg4.getInstanceArraySize(); i++)
	{
		Instance *instance=cg4.getInstance(i);
		if (instance->isNull()) continue; //skip null instances
		instance->setActionVariables(applyAction(instance->getActionIndex(), instance->getActionVariables(),i));
	}
	cg4.gameRender();
}

ActionVariables applyAction(int _actionIndex, ActionVariables _actVar, int _instanceIndex)
{
	//doing this so I don't have to type _actVar all the time
	int x = _actVar.x;
	int y = _actVar.y;
	int depth = _actVar.depth;
	int hspeed = _actVar.hspeed;
	int vspeed = _actVar.vspeed;
	Instance* current = cg4.getInstance(_instanceIndex);
	Timer* bulletTimer;

	switch (_actionIndex) //Never forget the break keyword after a case statement!!
	{
	case acSpaceship: 
		hspeed = 0;
		vspeed = 0;
		bulletTimer = cg4.getTimer(objSpaceship.inBulletTimer);
		//Make appropriate sprite changes
		if (objSpaceship.charge == 0) current->setSpriteIndex(sprSpaceship);
		if (objSpaceship.charge > 40) current->setSpriteIndex(sprSpaceshipCharging);
		if (objSpaceship.charge >= 100) current->setSpriteIndex(sprSpaceshipFullyCharged);

		if (cg4.checkEvent(evVK_A)) hspeed = -1;
		if (cg4.checkEvent(evVK_W)) vspeed = -1;
		if (cg4.checkEvent(evVK_S)) vspeed = 1;
		if (cg4.checkEvent(evVK_D)) hspeed = 1;

		if (cg4.checkEvent(evVK_SPACE)) {
			if (objSpaceship.charge < 100)objSpaceship.charge++;
			if (objSpaceship.canShoot == true) {
				int temp = cg4.addInstance(sprBullet, acBullet, x, y, 0);
				bulletTimer->resetTime();
				objSpaceship.canShoot = false;
			}
		}
		if (objSpaceship.canShoot == false && !cg4.checkEvent(evVK_SPACE))
		{
			if (bulletTimer->getElapsedTime() >= 250)
			{
				objSpaceship.canShoot = true;
			}
		}
		if (!cg4.checkEvent(evVK_SPACE))
		{
			if (objSpaceship.charge >= 100)
			{
				int temp = cg4.addInstance(sprFullChargeBullet, acBullet, x, y, 0);
				objSpaceship.charge = 0;
				break;
			}
			if (objSpaceship.charge > 40)
			{
				int temp = cg4.addInstance(sprChargeBullet, acBullet, x, y, 0);
				objSpaceship.charge = 0;
				break;
			}
		}
		if (cg4.checkCollision(_instanceIndex, objSpaceship2))
		{
			cg4.destroyInstance(_instanceIndex);
			int temp = cg4.addInstance(sprExplosion, acExplosion, x, y, 0);
		}
		break;
	case acBullet:
		vspeed = -2;
		if (y < 0) cg4.destroyInstance(_instanceIndex);
		if (cg4.checkCollision(_instanceIndex, objSpaceship2))
		{
			cg4.destroyInstance(_instanceIndex);
			int temp = cg4.addInstance(sprExplosion, acExplosion, 
				cg4.getInstance(objSpaceship2)->getX(), 
				cg4.getInstance(objSpaceship2)->getY(), 0);
 			cg4.destroyInstance(objSpaceship2);
		}
		break;
	case acSpaceship2:
		if (x > screen->screenWidth - cg4.getSprite(current->getSpriteIndex())->getSprWidth()) hspeed = -1;
		if (x < 0) hspeed = 1;
		break;
	case acExplosion:
		if (cg4.getSprite(current->getSpriteIndex())->isEndOfAnimation()) cg4.destroyInstance(_instanceIndex);
		break;
	default:
		return _actVar; //no break statement needed because 'return' acts as break
	}
	_actVar.x = x+hspeed;
	_actVar.y = y+vspeed;
	_actVar.depth = depth;
	_actVar.hspeed = hspeed;
	_actVar.vspeed = vspeed;
	return _actVar;
}