//ConsoleGraphics9
//Major overhaul. Making the main game actually derive a class from the game engine.
//The game engine will have virtual functions that the derived class will override.
//That way actions are defined inside the game engine, even though all the game code will exist outside the engine
//the outside program will gain access to everything inside the engine, so bridge needs to be managed anymore.
//Update 1.3.2020: overhaul complete
#include"main.h"

int main()
{
	srand(time(NULL));
	//Startup Routine
	HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	int dummy = _setmode(_fileno(stdout), _O_U16TEXT);//set unicode mode
	CONSOLE_CURSOR_INFO	cursorInfo = { 1,FALSE };
	SetConsoleCursorInfo(myHandle, &cursorInfo);
	screen = spaceGame.getScreen();
	SetConsoleScreenBufferSize(myHandle, { screen->screenWidth,screen->screenHeight });
	spaceGame.gameStart(&myHandle,&hwnd); //game starts here
	spaceGame.flipFpsSwitch(true); 
	while (1)//main game loop still happens in the main program
	{
		spaceGame.gameUpdate();
	}
	return 0;
}