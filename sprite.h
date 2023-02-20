#pragma once
#include<string>
#include<fstream>
#include<fcntl.h> //for unicode
#include<io.h> //for unicode
#include<locale>//for unicodefilereading
#include<codecvt>//for unicodefilereading
#include<Windows.h>

using namespace std;

struct Screen {
	SHORT screenWidth, screenHeight;
	wstring screenData;
};

class Sprite
{
public:
	int sprWidth;
	int sprHeight;
	int sprOriginX;
	int sprOriginY;
	wstring image; //this needs to be in the format of one concurrent 
	int noOfImages;
	int imagePerSec; //animation speed...
	bool endOfAnimation = false;
	int imageIndex;
	bool transparent = false;

	Sprite();
	void createSprite(string _filename); //exactly the same as the constructor
	void putSprite(int _x, int _y,Screen *_screen,ULONGLONG	_startTime);
	int getSprWidth();
	int getSprHeight();
	int getSprOriginX();
	int getSprOriginY();
	bool isEndOfAnimation();
};
