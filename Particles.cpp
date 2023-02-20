#include "particle.h"

ParticleSystem::ParticleSystem()
{
	//Initialize the particle system's variable as well as the one particle that is created in the array, *and* its 
	//variables as well
	x = 0;
	y = 0;
	hspeed = 0;
	vspeed = 0;
	//For the first particle that gets created when this system gets created
	particleArray[0].image = L"";
	particleArray[0].x = 0;
	particleArray[0].y = 0;
	particleArray[0].hspeed = 0;
	particleArray[0].vspeed = 0;
}

void ParticleSystem::createParticleSystem(wstring _image, int _x, int _y) //the x and y is for the system
{
	//chop up the string received, put each character into its own array along with its attributes
	/*if (_image.length()==0)*/
}