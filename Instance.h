#pragma once
#include<windows.h>
#include<string>

using namespace std;

//Instances consists of a group of preinstalled variables like x,y,depth, hspeed and vspeed.
//More might be added later, but these variables will always reside for the first slots of variable
//storage. Custom variable slots start later. So, these first group of variables will always have the same indeces
//Indeces are in number form inside the engine, but are represented using int variables in the main program with the same name.
//So during instance creation in the main game, these group of indices will always need to be prepared.
//Store these indices in the variable storage by using this classes constructor
//struct ActionVariables
//{
//	int x = 0, y = 0, depth = 0, hspeed = 0, vspeed = 0;
//};

class Instance //The class definition needs to appear before its usage.
{
private:
	//ActionVariables actionVariables;
	int actionIndex;
	int spriteIndex;
	int x, y, depth, hspeed, vspeed;
	bool firstDraw = true; //C.5
	ULONGLONG startTime = GetTickCount64(); //used for sprite animation
	bool Null = false;
	

	
	//event status identifiers indices, naming convention, put constants (eg events) in all caps
	const int insEventArraySize = 1; //ALso look at C.7
	const int evInsENDOFANIMATION = 1000;

	//event storage array, manually made because these are predefined
	bool* insEventArray = new bool[insEventArraySize];	

public:
	//Constructor
	Instance();
	Instance(int _x, int _y, int _depth);
	Instance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth);
	void createInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth);
	//Overloaded operators
	void instanceCopy(Instance _instance); //C.8
	
	//ActionVariables methods
	//ActionVariables getActionVariables();
	//void setActionVariables(ActionVariables _actVar);

	int getActionIndex();
	int getSpriteIndex();
	void setSpriteIndex(int _spriteIndex); //make sure C.5 for this when changing sprites

	//concerned with sprite animation
	ULONGLONG *getStartTime();
	bool* getFirstDraw();

	//nullifiers
	void makeNull();
	bool isNull();
	void setNull(bool _Null);

	//getters
	int getX();
	int getY();
	int getDepth();
	int getHSpeed();
	int getVSpeed();

	//setters
	void setX(int _x);
	void setY(int _y);
	void setDepth(int _depth);
	void setHSpeed(int _hspeed);
	void setVSpeed(int _vspeed);

	//event methods
	void updateInstanceEvent(); //C.6
	bool checkInsEvent(int _insEventIndex);
	void setInsEvent(int _insEventIndex, bool _status);

	
};
