#include "Instance.h"

Instance::Instance()
{
	spriteIndex = -1;
	actionIndex = -1;
	x = 0;
	y = 0;
	depth = 0;
	hspeed = 0;
	vspeed = 0;
}
Instance::Instance(int _x, int _y, int _depth)
{
	x = _x;
	y = _y;
	depth = _depth;
	hspeed = 0;
	vspeed = 0;
	spriteIndex = -1;
	actionIndex = -1;
}

Instance::Instance(int _spriteIndex, int _actionIndex, int _x, int _y, int _depth)
{
	spriteIndex = _spriteIndex;
	actionIndex = _actionIndex;
	x = _x;
	y = _y;
	depth = _depth;
	hspeed = 0;
	vspeed = 0;
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
	return x;
}
int Instance::getY()
{
	return y;
}
int Instance::getDepth()
{
	return depth;
}

int Instance::getHSpeed()
{
	return hspeed;
}
int Instance::getVSpeed()
{
	return vspeed;
}

 //Setters
void Instance::setX(int _x)
{
	x = _x;
}
void Instance::setY(int _y)
{
	y = _y;
}
void Instance::setDepth(int _depth)
{
	depth=_depth;
}

void Instance::setHSpeed(int _hspeed)
{
	hspeed=_hspeed;
}
void Instance::setVSpeed(int _vspeed)
{
	vspeed=_vspeed;
}
bool *Instance::getFirstDraw()
{
	return &firstDraw;
}

void Instance::updateInstanceEvent()
{
	//update the events
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
	insEventArray = _instance.insEventArray;
	x = _instance.x;
	y = _instance.y;
	depth = _instance.depth;
	hspeed = _instance.hspeed;
	vspeed = _instance.vspeed;
}