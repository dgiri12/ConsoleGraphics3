#pragma once
#include<windows.h>
#include<string>

using namespace std;

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
	
	//user defined int variables
	struct UserVariableInt
	{
		string name;
		int value;
	};
	int userVariableIntIndexCounter = 0;//the first sprite index would be index '0' that way
	UserVariableInt* userVariableIntArray = new UserVariableInt[1];
	UserVariableInt* tempUserVariableIntArray = nullptr;
	int userVariableIntArraySize = 1;
	bool firstUserVariableIntLoaded = false;

	//user defined boolean variables
	struct UserVariableBool
	{
		string name;
		bool value;
	};
	int userVariableBoolIndexCounter = 0;//the first Bool index would be index '0' that way
	UserVariableBool* userVariableBoolArray = new UserVariableBool[1];
	UserVariableBool* tempUserVariableBoolArray = nullptr;
	int userVariableBoolArraySize = 1;
	bool firstUserVariableBoolLoaded = false;

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

	//UserVariableInt methods
	int addUserVariableInt(string _name, int _value);
	int getUserVariableIntValue(int _userVariableIntIndex);
	void setUserVariableIntValue(int _userVariableIntIndex,int _userVariableIntValue);

	//UserVariableBool methods
	int addUserVariableBool(string _name, bool _value);
	bool getUserVariableBoolValue(int _userVariableBoolIndex);
	void setUserVariableBoolValue(int _userVariableBoolIndex, bool _userVariableBoolValue);
};
