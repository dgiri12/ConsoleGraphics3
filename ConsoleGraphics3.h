#pragma once
#include<iostream>
#include<cstdlib>
#include<time.h>
#include<Windows.h>
#include<string>
#include"sprite.h"
#include"Instance.h"
#include"Timer.h"

#define eventArraySize 6
#define evVK_A 0
#define evVK_D 1
#define evVK_W 2
#define evVK_S 3
#define evVK_SPACE 4
#define evVK_E 5

//C.7
#define insEventArraySize 1
#define evInsENDOFANIMATION 1000

using namespace std;

//C.4


class ConsoleGraphics3
{
protected:
	//Global class variables
	DWORD dummy = 0;;
	ULONGLONG FPSCounterTime = GetTickCount64(); //used for fps calculation
	Screen screen = { 140,45,L"" }; //Anything made from this class will forever have these dimensions
	wstring screenText = L"";
	HANDLE *myHandle;
	
	string GlobalTemp = "ASCII";
	bool fpsSwitch = false;
	int frame = 0;

	//Sprite variables
	int spriteIndexCounter = 0;//the first sprite index would be index '0' that way
	Sprite* spriteArray = new Sprite[1];
	Sprite* tempSpriteArray = nullptr;
	int spriteArraySize = 1;
	bool firstSpriteLoaded = false;

	//Instance Variables
	int instanceIndexCounter = 0;//the first sprite index would be index '0' that way
	Instance* instanceArray = new Instance[1];
	Instance* tempInstanceArray = nullptr;
	int instanceArraySize = 1;
	bool firstInstanceLoaded = false;

	//Timer Variables
	int timerIndexCounter = 0;//the first sprite index would be index '0' that way
	Timer* timerArray = new Timer[1];
	Timer* tempTimerArray = nullptr;
	int timerArraySize = 1;
	bool firstTimerLoaded = false;

	//Events
	//Events switch on and off throughout the running of the game.
	//the eventarray is just a group of switches that turn on and off when something
	//the engine then checks the status of these 'switches' to trigger actions
	//The engine constantly updates these.
	bool* eventArray = new bool[eventArraySize];

protected://Function declaration
	int getFps(int _frame);
	void gameRender();
	
	
	int addSprite(string _filename);//C.3
	int addInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth);
	int addTimer();
	bool checkEvent(int _eventIndex);
	void setEvent(int _eventIndex, bool _status);
	int getInstanceArraySize();
	Instance* getInstance(int _instanceIndex);
	Timer* getTimer(int _timerIndex);
	void destroyInstance(int _instanceIndex);
	Sprite* getSprite(int _spriteIndex);
	//Check the collision of first instance against second instance
	bool checkCollision(int _instanceIndex1, int _instanceIndex2);
	void drawText(int _x, int _y, wstring _text);
	void setScreenText(wstring _screenText);
public:
	Screen* getScreen();
	void gameStart(HANDLE* _handle, HWND* _hwnd);
	void flipFpsSwitch(bool _fpsSwitch);
	virtual void onInstanceCreateApplyAction(int _actionIndex, int _instanceIndex) {}
	virtual void gameUpdate() {}
	virtual void ongoingInstanceApplyAction(int _actionIndex, int _instanceIndex) {}
};