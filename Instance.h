#pragma once
#include<windows.h>

struct ActionVariables
{
	int x = 0, y = 0, depth = 0, hspeed = 0, vspeed = 0;
};

class Instance //The class definition needs to appear before its usage.
{
private:
	ActionVariables actionVariables;
	int actionIndex;
	int spriteIndex;
	ULONGLONG startTime = GetTickCount64(); //used for sprite animation
	bool Null = false;


public:
	//Constructor
	Instance();
	Instance(int _x, int _y, int _depth);
	Instance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth);
	void createInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth);
	ActionVariables getActionVariables();
	void setActionVariables(ActionVariables _actVar);
	int getActionIndex();
	int getSpriteIndex();
	void setSpriteIndex(int _spriteIndex);
	ULONGLONG getStartTime();
	void makeNull();
	bool isNull();
	void setNull(bool _Null);
	int getX();
	int getY();
	int getDepth();
	int getHSpeed();
	int getVSpeed();
};
