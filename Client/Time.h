#pragma once
#define NUMBER_SAMPLES 10
#define MILISECONDS 1000
#define DESIRED_FPS 60
#define DESIRED_FRAMETIME (MILISECONDS / DESIRED_FPS)
#define MAX_STEPS 6
#define MAX_PRINT_MARKER 10
class Time
{
private:
	int index;
	int count;
	int samples[NUMBER_SAMPLES];
	int previousTime;
	int printMarker;
	float fps;
	float deltaTime;
	float frameTime;
public:
	Time();
	void calculateFPS();
	void printFPS();
	float getFPS();
	float getFrameTime();
	float getDeltaTime();
	float getTime();
};

