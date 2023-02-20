#include"ConsoleGraphics3.h"

void ConsoleGraphics3::gameStart(HANDLE *_handle, HWND *_hwnd)
{
	//Initialize the screen
	myHandle = _handle;
	
	MoveWindow(*_hwnd, 0, 0, 1024, 768, FALSE);

	wstring s = L" ";
	for (int i = 0; i < screen.screenWidth * screen.screenHeight; i++)
	{
		screen.screenData += s;
	}//fills screen with blanks to get it ready
	for (int i = 0; i < eventArraySize; i++) { eventArray[i] = false; } //Initialize events array (set to false)
}

int ConsoleGraphics3::getFps(int _frame)
{
	if (fpsSwitch == false) return _frame;
	//print the fps
	if (GetTickCount64() >= sysTime + 1000) {
		string title = GlobalTemp + to_string(_frame);
		SetConsoleTitle(title.c_str());
		sysTime = GetTickCount64();
		return 0;
	}
	return _frame;
}


void ConsoleGraphics3::flipFpsSwitch(bool _switch)
{
	fpsSwitch = _switch;
}

Screen* ConsoleGraphics3::getScreen()
{
	return &screen;
}

int ConsoleGraphics3::addSprite(string _filename)
{
	//Different routine if the sprite is the first one to be added
	if (firstSpriteLoaded == false) {
		firstSpriteLoaded = true;
		spriteArray[spriteIndexCounter].createSprite(_filename);
		return spriteIndexCounter;
	}
	int newSize = spriteArraySize + 1;
	tempSpriteArray = new Sprite[newSize];
	for (int i = 0; i < spriteArraySize; i++)
	{
		tempSpriteArray[i] = spriteArray[i];
	}//copies older sprites into new temp location
	tempSpriteArray[newSize - 1].createSprite(_filename);//final temp position is a fresh sprite
	//so create it using filename provided.
	//tempSpriteArray contains new data, so delete the old array, and have the old point to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] spriteArray;
	spriteArray = tempSpriteArray;
	tempSpriteArray = nullptr;
	spriteArraySize = newSize;
	spriteIndexCounter++;
	return spriteIndexCounter;
}

int ConsoleGraphics3::addInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	//Different routine if the instance is the first one to be added
	if (firstInstanceLoaded == false) {
		firstInstanceLoaded = true;
		instanceArray[instanceIndexCounter].createInstance(_spriteIndex, _actionIndex, _x, _y,_depth);
		return instanceIndexCounter;
	}
	//Now before increasing size, check if this new instance can take place of an existing null instance,
	//if so, reassign the instanceIndex to that new instance
	for (int i = 0; i < instanceArraySize; i++)
	{
		if (instanceArray[i].isNull())
		{
			instanceArray[i].setNull(false);
			instanceArray[i].createInstance(_spriteIndex, _actionIndex, _x, _y, _depth);
			return i;
		}
	}

	int newSize = instanceArraySize + 1;
	tempInstanceArray = new Instance[newSize];
	for (int i = 0; i < instanceArraySize; i++)
	{
		tempInstanceArray[i] = instanceArray[i];
	}//copies older instances into new temp location
	tempInstanceArray[newSize - 1].createInstance(_spriteIndex, _actionIndex, _x, _y, _depth);//final temp position is a fresh instance
	//so create it using parameters provided.
	//tempInstanceArray contains new data, so delete the old array, and have the old point to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] instanceArray;
	instanceArray = tempInstanceArray;
	tempInstanceArray = nullptr;
	instanceArraySize = newSize;
	instanceIndexCounter++;
	return instanceIndexCounter;
}

int ConsoleGraphics3::addTimer()
{
	//Different routine if the instance is the first one to be added
	if (firstTimerLoaded == false) {
		firstTimerLoaded = true;
		timerArray[timerIndexCounter].createTimer();
		return timerIndexCounter;
	}
	//Now before increasing size, check if this new timer can take place of an existing unused time,
	//if so, reassign the timerIndex to that new timer
	for (int i = 0; i < timerArraySize; i++)
	{
		if (timerArray[i].isNull())
		{
			timerArray[i].setNull(false);
			timerArray[i].resetTime();
			return i;
		}
	}

	int newSize = timerArraySize + 1;
	tempTimerArray = new Timer[newSize];
	for (int i = 0; i < timerArraySize; i++)
	{
		tempTimerArray[i] = timerArray[i];
	}//copies older instances into new temp location
	tempTimerArray[newSize - 1].createTimer();//final temp position is a fresh instance
	//so create it using parameters provided.
	//tempInstanceArray contains new data, so delete the old array, and have the old point to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] timerArray;
	timerArray = tempTimerArray;
	tempTimerArray = nullptr;
	timerArraySize = newSize;
	timerIndexCounter++;
	return timerIndexCounter;
}


int ConsoleGraphics3::getInstanceArraySize()
{
	return instanceArraySize;
}

Instance* ConsoleGraphics3::getInstance(int _instanceIndex)
{
	return &instanceArray[_instanceIndex];
}
void ConsoleGraphics3::gameRender()
{
	ActionVariables actVar;
	for (int i = 0; i < instanceArraySize; i++)
	{
		if (instanceArray[i].isNull()) continue; //skip if it's a null instance
		actVar = instanceArray[i].getActionVariables();
		spriteArray[instanceArray[i].getSpriteIndex()].putSprite(actVar.x, actVar.y, &screen, instanceArray[i].getStartTime());
	}
	//Then print screen variable onto the console
	WriteConsoleOutputCharacterW(*myHandle, screen.screenData.c_str(), screen.screenWidth * screen.screenHeight, { 0,0 }, &dummy);
	frame = getFps(frame);
	frame++;
}

bool ConsoleGraphics3::checkEvent(int _eventIndex)
{
	if (_eventIndex<eventArraySize && _eventIndex>=0)	return eventArray[_eventIndex];
	return false;
}

void ConsoleGraphics3::setEvent(int _eventIndex,bool _status)
{
	if (_eventIndex < eventArraySize && _eventIndex >= 0) eventArray[_eventIndex] = _status;
}

Sprite* ConsoleGraphics3::getSprite(int _spriteIndex)
{
	return &spriteArray[_spriteIndex];
}

void ConsoleGraphics3::destroyInstance(int _instanceIndex)
{
	instanceArray[_instanceIndex].makeNull();
}
Timer* ConsoleGraphics3::getTimer(int _timerIndex)
{
	return &timerArray[_timerIndex];
}
bool ConsoleGraphics3::checkCollision(int _instanceIndex1, int _instanceIndex2)
{
	Instance* instance1 = &instanceArray[_instanceIndex1];
	Instance* instance2 = &instanceArray[_instanceIndex2];

	int origX1 = getSprite(instance1->getSpriteIndex())->getSprOriginX();
	int origY1 = getSprite(instance1->getSpriteIndex())->getSprOriginY();

	int origX2 = getSprite(instance2->getSpriteIndex())->getSprOriginX();
	int origY2 = getSprite(instance2->getSpriteIndex())->getSprOriginY();

	int left1 = instance1->getX()-origX1;
	int top1 = instance1->getY() - origY1;
	int right1 = instance1->getX() - origX1+ getSprite(instance1->getSpriteIndex())->getSprWidth();
	int bottom1 = instance1->getY() - origY1+ getSprite(instance1->getSpriteIndex())->getSprHeight();
	
	int left2 = instance2->getX() - origX2;;
	int top2 = instance2->getY() -origY2;
	int right2 = instance2->getX() -origX2+getSprite(instance2->getSpriteIndex())->getSprWidth();
	int bottom2 = instance2->getY() -origY2+ getSprite(instance2->getSpriteIndex())->getSprHeight();
	
	if (left1 > left2 && left1<right2 && top1>top2&& top1 < bottom2) return true; //checks top left corner of bounding box
	if (right1 > left2&& right1 < right2 && bottom1>top2&& bottom1 < bottom2) return true; //checks bottom right of bounding boxS
	return false;
 }

void ConsoleGraphics3::drawText(int _x, int _y, wstring _text)
{
	int pos = 0;
	for (int i = _x; i < _x + _text.length(); i++)
		{
			if (i < screen.screenWidth && _y < screen.screenHeight && i >= 0 && _y >= 0)//draw within the screen
			{
				screen.screenData.replace(_y * screen.screenWidth + i, 1, _text.substr(pos, 1));
			}
			pos++;
		}
}