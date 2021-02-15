#pragma once
#define NUMBER_SAMPLES 10
#define MILISECONDS 1000
#define DESIRED_FPS 60
#define DESIRED_FRAMETIME (MILISECONDS / DESIRED_FPS)
#define MAX_STEPS 6
#define MAX_PRINT_MARKER 10
class FPS
{
private:
	int index;
	int count;
	int samples[NUMBER_SAMPLES];
	int previousTime;
	int printMarker;
	float fps;
	float deltaTime;
public:
	FPS();
	void calculateFPS();
	void printFPS();
	float getFPS();
	float getDeltaTime();
};

