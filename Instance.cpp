#include "Instance.h"

Instance::Instance()
{
	spriteIndex = -1;
	actionIndex = -1;
	dummy=addVariableInt("x", 0);
	dummy=addVariableInt("y", 0);
	dummy = addVariableInt("depth", 0);
	dummy = addVariableInt("hspeed", 0);
	dummy = addVariableInt("vspeed", 0);
}
Instance::Instance(int _x, int _y, int _depth)
{
	dummy = addVariableInt("x", _x);
	dummy = addVariableInt("y", _y);
	dummy = addVariableInt("depth", _depth);
	dummy = addVariableInt("hspeed", 0);
	dummy = addVariableInt("vspeed", 0);
	spriteIndex = -1;
	actionIndex = -1;
}

Instance::Instance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	spriteIndex = _spriteIndex;
	actionIndex = _actionIndex;
	dummy = addVariableInt("x", _x);
	dummy = addVariableInt("y", _y);
	dummy = addVariableInt("depth", _depth);
	dummy = addVariableInt("hspeed", 0);
	dummy = addVariableInt("vspeed", 0);
}
void Instance::createInstance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	spriteIndex = _spriteIndex;
	actionIndex = _actionIndex;
	//C.4
	setX(_x);
	setY(_y);
	setDepth(_depth);
	setHSpeed(0);
	setVSpeed(0);
	firstDraw = true;
	startTime = GetTickCount64();
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
ULONGLONG *Instance::getStartTime()
{
	return &startTime;
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
		setX(0); 
		setY(0);
		setDepth(0);
		setHSpeed(0);
		setVSpeed(0);
		Null = true;
		firstDraw = true;
	}
}
void Instance::setNull(bool _Null)
{
	Null = _Null;
}
int Instance::getX()
{
	return variableIntArray[0].value;
}
int Instance::getY()
{
	return variableIntArray[1].value;
}
int Instance::getDepth()
{
	return variableIntArray[2].value;
}

int Instance::getHSpeed()
{
	return variableIntArray[3].value;
}
int Instance::getVSpeed()
{
	return variableIntArray[4].value;
}

 //Setters
void Instance::setX(int _x)
{
	variableIntArray[0].value = _x;
}
void Instance::setY(int _y)
{
	variableIntArray[1].value = _y;
}
void Instance::setDepth(int _depth)
{
	variableIntArray[2].value=_depth;
}

void Instance::setHSpeed(int _hspeed)
{
	variableIntArray[3].value=_hspeed;
}
void Instance::setVSpeed(int _vspeed)
{
	variableIntArray[4].value=_vspeed;
}

int Instance::addVariableInt(string _name, int _value)
{
	//Different routine if the  variable is the first one to be added
	if (firstVariableIntLoaded == false) {
		firstVariableIntLoaded = true;
		variableIntArray[variableIntIndexCounter].name = _name;
		variableIntArray[variableIntIndexCounter].value = _value;
		return variableIntIndexCounter;
	}
	int newSize = variableIntArraySize + 1;
	tempVariableIntArray = new VariableInt[newSize];
	for (int i = 0; i < variableIntArraySize; i++)
	{
		tempVariableIntArray[i] = variableIntArray[i];
	}//copies older sprites into new temp location
	tempVariableIntArray[newSize - 1].name = _name;
	tempVariableIntArray[newSize - 1].value = _value;//final temp position is a fresh sprite
	//so create it using filename provided.
	//tempSpriteArray contains new data, so delete the old array, and have the old point to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] variableIntArray;
	variableIntArray = tempVariableIntArray;
	tempVariableIntArray = nullptr;
	variableIntArraySize = newSize;
	variableIntIndexCounter++;
	return variableIntIndexCounter;
}

int Instance::getVariableIntValue(int _variableIntIndex)
{
	return variableIntArray[_variableIntIndex].value;
}

void Instance::setVariableIntValue(int _variableIntIndex, int _variableIntValue)
{
	variableIntArray[_variableIntIndex].value = _variableIntValue;
}

//VariableBool methods

int Instance::addVariableBool(string _name, bool _value)
{
	//Different routine if the  variable is the first one to be added
	if (firstVariableBoolLoaded == false) {
		firstVariableBoolLoaded = true;
		variableBoolArray[variableBoolIndexCounter].name = _name;
		variableBoolArray[variableBoolIndexCounter].value = _value;
		return variableBoolIndexCounter;
	}
	int newSize = variableBoolArraySize + 1;
	tempVariableBoolArray = new VariableBool[newSize];
	for (int i = 0; i < variableBoolArraySize; i++)
	{
		tempVariableBoolArray[i] = variableBoolArray[i];
	}//copies older sprites into new temp location
	tempVariableBoolArray[newSize - 1].name = _name;
	tempVariableBoolArray[newSize - 1].value = _value;//final temp position is a fresh sprite
	//so create it using filename provided.
	//tempSpriteArray contains new data, so delete the old array, and have the old poBool to the new one,
	//and nullify the new one, to be reused later. Update values of remaining variables.
	delete[] variableBoolArray;
	variableBoolArray = tempVariableBoolArray;
	tempVariableBoolArray = nullptr;
	variableBoolArraySize = newSize;
	variableBoolIndexCounter++;
	return variableBoolIndexCounter;
}

bool Instance::getVariableBoolValue(int _variableBoolIndex)
{
	return variableBoolArray[_variableBoolIndex].value;
}

void Instance::setVariableBoolValue(int _variableBoolIndex, bool _variableBoolValue)
{
	variableBoolArray[_variableBoolIndex].value = _variableBoolValue;
}
bool *Instance::getFirstDraw()
{
	return &firstDraw;
}

void Instance::updateInstanceEvent()
{
	//update the 
}
void Instance::setInsEvent(int _insEventIndex, bool _status)
{
	insEventArray[_insEventIndex-1000] = _status; //insEv indices start from 1000, so calibrate the value
}
bool Instance::checkInsEvent(int _insEventIndex)
{
	return insEventArray[_insEventIndex-1000];
}
void Instance::instanceCopy(Instance _instance)
{
	actionIndex=_instance.actionIndex;
	spriteIndex=_instance.spriteIndex;
	firstDraw = _instance.firstDraw; //C.5
	startTime = _instance.startTime;
	Null = _instance.Null;
	variableIntIndexCounter = _instance.variableIntIndexCounter;//the first variableInt index would be index '4' that way
	variableIntArray = _instance.variableIntArray;
	tempVariableIntArray = _instance.tempVariableIntArray;
	variableIntArraySize = _instance.variableIntArraySize;
	firstVariableIntLoaded = _instance.firstVariableIntLoaded;
	variableBoolIndexCounter = _instance.variableBoolIndexCounter;//the first Bool index would be index '0' that way
	variableBoolArray = _instance.variableBoolArray;
	tempVariableBoolArray = _instance.tempVariableBoolArray;
	variableBoolArraySize = _instance.variableBoolArraySize;
	firstVariableBoolLoaded = _instance.firstVariableBoolLoaded;
	insEventArray = _instance.insEventArray;
}