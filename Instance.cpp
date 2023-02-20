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