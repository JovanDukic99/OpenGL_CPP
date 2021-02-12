#pragma once
#define NUMBER_SAMPLES 10
#define MILISECONDS 1000
class FPS
{
private:
	int index;
	int count;
	int samples[NUMBER_SAMPLES];
	int previousTime;
	float fps;
public:
	FPS();
	void calculateFPS();
	float getFPS();
};

