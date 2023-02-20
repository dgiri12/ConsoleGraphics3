#pragma once

#include<string>

using namespace std;

struct Particle
{
	wstring image; //this is usually a single character, or more characters that behave as a single unit
	int x, y, hspeed, vspeed;
};
class ParticleSystem
{
	//an image file in the form of a concurrent string needs to be loaded. This class dissects each character in the image,
	//and adds them into an array, and each character will have property as described by the particle structure
private:
	//the particle system itself will have its own x,y, etc. The particle inside it will follow relative coordinates
	int x, y, hspeed, vspeed;

	//Array that stores individual particles
	//the first particle index would be index '0' that way
	Particle* particleArray = new Particle[1];

	//Methods required
	//constructors
	ParticleSystem();
	void createParticleSystem(wstring _image, int _x, int _y); //called by the game engine, when adding a particle system to 
	//its array storage.
	void onParticleCreateApplyAction();//iterate through each particle, and apply onCreation actions on them, like set their initial speed for eg
	//Methods for particles. You can specify individual values for each particle, or give them a behavior as a whole
	//Use applyAction technique for behaviors, depending on what predefined behavior has been activated, use switch case technique
	void applyAction();//iterate through each particle, and apply actions to them while they are existing
	
	//Methods for the particle system
	void setParticleSystemX(int _x);
	void setParticleSystemY(int _y);
	void setParticleSystemHSpeed(int _hspeed);
	void setParticleSystemVSpeed(int _vspeed);

	

};