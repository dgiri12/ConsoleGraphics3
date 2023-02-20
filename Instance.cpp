#include "Instance.h"

Instance::Instance()
{
	spriteIndex = -1;
	actionIndex = -1;
	actionVariables.x = 0;
	actionVariables.y = 0;
	actionVariables.depth = 0;
}
Instance::Instance(int _x, int _y, int _depth)
{
	actionVariables.x = _x;
	actionVariables.y = _y;
	actionVariables.depth = _depth;
	spriteIndex = -1;
	actionIndex = -1;
}

Instance::Instance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	spriteIndex = _spriteIndex;
	actionIndex = _actionIndex;
	actionVariables.x = _x;
	actionVariables.y = _y;
	actionVariables.depth = _depth;
}
void Instance::createInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	spriteIndex = _spriteIndex;
	actionIndex = _actionIndex;
	actionVariables.x = _x;
	actionVariables.y = _y;
	actionVariables.depth = _depth;
}
ActionVariables Instance::getActionVariables()
{
	return actionVariables;
}
void Instance::setActionVariables(ActionVariables _actVar)
{
	actionVariables = _actVar;
}
int Instance::getActionIndex()
{
	return actionIndex;
}
int Instance::getSpriteIndex()
{
	return spriteIndex;
}
void Instance::setSpriteIndex(int _spriteIndex)
{
	spriteIndex = _spriteIndex;
}
ULONGLONG Instance::getStartTime()
{
	return startTime;
}
bool Instance::isNull()
{
	return Null;
}
void Instance::makeNull()
{
	if (Null == false) {


		spriteIndex = -1;
		actionIndex = -1;
		actionVariables.x = 0;
		actionVariables.y = 0;
		actionVariables.depth = 0;
		actionVariables.hspeed = 0;
		actionVariables.vspeed = 0;
		Null = true;
	}
}
void Instance::setNull(bool _Null)
{
	Null = _Null;
}
int Instance::getX()
{
	return actionVariables.x;
}
int Instance::getY()
{
	return actionVariables.y;
}
int Instance::getDepth()
{
	return actionVariables.depth;
}

int Instance::getHSpeed()
{
	return actionVariables.hspeed;
}
int Instance::getVSpeed()
{
	return actionVariables.vspeed;
}

int Instance::addUserVariableInt(string _name, int _value)
{
	//Different routine if the user variable is the first one to be added
	if (firstUserVariableIntLoaded == false) {
		firstUserVariableIntLoaded = true;
		userVariableIntArray[userVariableIntIndexCounter].name = _name;
		userVariableIntArray[userVariableIntIndexCounter].value = _value;
		return userVariableIntIndexCounter;
	}
	int newSize = userVariableIntArraySize + 1;
	userVariableIntArray = new UserVariableInt[newSize];
	for (int i = 0; i < userVariableIntArraySize; i++)
	{
		tempUserVariableIntArray[i] = userVariableIntArray[i];
	}//copies older sprites into new temp location
	tempUserVariableIntArray[newSize - 1].name = _name;
	tempUserVariableIntArray[newSize - 1].value = _value;//final temp position is a fresh sprite
	//so create it using filename provided.
	//tempSpriteArray contains new data, so delete the old array, and have the old point to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] userVariableIntArray;
	userVariableIntArray = tempUserVariableIntArray;
	tempUserVariableIntArray = nullptr;
	userVariableIntArraySize = newSize;
	userVariableIntIndexCounter++;
	return userVariableIntIndexCounter;
}

int Instance::getUserVariableIntValue(int _userVariableIntIndex)
{
	return userVariableIntArray[_userVariableIntIndex].value;
}

void Instance::setUserVariableIntValue(int _userVariableIntIndex, int _userVariableIntValue)
{
	userVariableIntArray[_userVariableIntIndex].value = _userVariableIntValue;
}

//userVariableBool methods

int Instance::addUserVariableBool(string _name, bool _value)
{
	//Different routine if the user variable is the first one to be added
	if (firstUserVariableBoolLoaded == false) {
		firstUserVariableBoolLoaded = true;
		userVariableBoolArray[userVariableBoolIndexCounter].name = _name;
		userVariableBoolArray[userVariableBoolIndexCounter].value = _value;
		return userVariableBoolIndexCounter;
	}
	int newSize = userVariableBoolArraySize + 1;
	userVariableBoolArray = new UserVariableBool[newSize];
	for (int i = 0; i < userVariableBoolArraySize; i++)
	{
		tempUserVariableBoolArray[i] = userVariableBoolArray[i];
	}//copies older sprites into new temp location
	tempUserVariableBoolArray[newSize - 1].name = _name;
	tempUserVariableBoolArray[newSize - 1].value = _value;//final temp position is a fresh sprite
	//so create it using filename provided.
	//tempSpriteArray contains new data, so delete the old array, and have the old poBool to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] userVariableBoolArray;
	userVariableBoolArray = tempUserVariableBoolArray;
	tempUserVariableBoolArray = nullptr;
	userVariableBoolArraySize = newSize;
	userVariableBoolIndexCounter++;
	return userVariableBoolIndexCounter;
}

bool Instance::getUserVariableBoolValue(int _userVariableBoolIndex)
{
	return userVariableBoolArray[_userVariableBoolIndex].value;
}

void Instance::setUserVariableBoolValue(int _userVariableBoolIndex, bool _userVariableBoolValue)
{
	userVariableBoolArray[_userVariableBoolIndex].value = _userVariableBoolValue;
}