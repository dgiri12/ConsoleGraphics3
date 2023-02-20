#pragma once
#include<Windows.h>

class Timer
{
private:
	ULONGLONG startTime = GetTickCount64();
	bool Null = false;
public:
	void createTimer()
	{
		startTime = GetTickCount64();
		Null = false;
	}
	ULONGLONG getElapsedTime()
	{
		return GetTickCount64() - startTime;
	}//how much time has passed since it's creation (milliseconds)
	void resetTime()
	{
		startTime = GetTickCount64();
	}
	bool isNull()
	{
		return Null;
	}
	void makeNull()
	{
		if (Null == false) Null = true;
	}
	void setNull(bool _Null)
	{
		Null = _Null;
	}
};