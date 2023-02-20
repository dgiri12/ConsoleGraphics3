#include"sprite.h"


Sprite::Sprite()
{
	sprWidth = 0;
	sprHeight = 0;
	image = L"";
	sprOriginX=0;
	sprOriginY=0;
	noOfImages=1;
	imagePerSec=1;
	bool transparent = false;
};


//Creates a custom image
void Sprite::createSprite(string _filename)
{
	int lineCounter = 0;
	wifstream inputFile(_filename, ios::binary);//open file in binary mode
	//switch file io into utf16 mode
	inputFile.imbue(std::locale(inputFile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

	wstring inputString = L"";
	wstring outputString = L"";

	while (getline(inputFile, inputString))
	{
		if (lineCounter == 0)
		{
			sprWidth = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 1)
		{
			sprHeight = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 2)
		{
			noOfImages = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 3)
		{
			imagePerSec = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 4)
		{
			transparent = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 5)
		{
			sprOriginX = stoi(inputString);
			lineCounter++;
			continue;
		}
		if (lineCounter == 6)
		{
			sprOriginY = stoi(inputString);
			lineCounter++;
			continue;
		}
		outputString += inputString;
		lineCounter++;
	}
	image = outputString;
	//C.2

	for (int i = 0; i < image.length(); i++)
	{
		wstring str = image.substr(i, 1);
		if (str == L"\r")
		{
			image.replace(i, 1, L"");
		}
	}
	inputFile.close();

};

void Sprite::putSprite(int _x, int _y,Screen *_screen, ULONGLONG _startTime )
{
	_y = _y - sprOriginY;
	_x = _x - sprOriginX;
	ULONGLONG seconds = floor((GetTickCount64() - _startTime) / (1000 / imagePerSec));
	imageIndex = floor(seconds % noOfImages);
	if (imageIndex > noOfImages) {
		imageIndex = 0;
	}
	int imagePos = 0;
	if (imageIndex > 0) imagePos = sprWidth * sprHeight * imageIndex;
	wstring imageStr = L"";
	if (transparent == false) {
		for (int j = _y; j < _y + sprHeight; j++)
		{
			for (int i = _x; i < _x + sprWidth; i++)
			{
				imageStr = image.substr(imagePos, 1);
				if (i < _screen->screenWidth && j < _screen->screenHeight && i>=0 && j >=0)//draw within the screen
				{
					_screen->screenData.replace(j * _screen->screenWidth + i, 1, imageStr);
				}
				imagePos++;
			}
		}
	}
	if (transparent == true)
	{
		for (int j = _y; j < _y+ sprHeight; j++)
		{
			for (int i = _x; i < _x+ sprWidth; i++)
			{
				imageStr = image.substr(imagePos, 1);
				if (i < _screen->screenWidth && j < _screen->screenHeight && i >= 0 && j >= 0)//draw within the screen
				{
					if (imageStr != L" " && imageStr != L" "/*C.1*/) _screen->screenData.replace(j * _screen->screenWidth + i, 1, imageStr);
				}
				imagePos++;
			}
		}
	}
};

int Sprite::getSprWidth()
{
	return sprWidth;
};
int Sprite::getSprHeight()
{
	return sprHeight;
};
int Sprite::getSprOriginX()
{
	return sprOriginX;
}
int Sprite::getSprOriginY()
{
	return sprOriginY;
}
bool Sprite::isEndOfAnimation()
{
	return imageIndex == noOfImages-1;
}