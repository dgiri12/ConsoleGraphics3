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
private:
	int sprWidth;
	int sprHeight;
	int sprOriginX;
	int sprOriginY;
	wstring image; //this needs to be in the format of one concurrent 
	int noOfImages;
	int imagePerSec; //animation speed...
	int imageIndex;
	bool transparent = false;
public:
	Sprite();
	void createSprite(string _filename); //exactly the same as the constructor
	void drawSprite(int _x, int _y,Screen *_screen,ULONGLONG *_startTime, bool *_firstDraw);
	int getSprWidth();
	int getSprHeight();
	int getSprOriginX();
	int getSprOriginY();
	int getImageIndex();
	int getNoOfImages();
};
