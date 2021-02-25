#include "Time.h"
#include <SDL/SDL.h>
#include <iostream>

Time::Time() : index(0), count(0), samples(), previousTime(0), fps(0.0f), deltaTime(0.0f), frameTime(0.0f), printMarker(0) {

}

void Time::calculateFPS() {
	// get current time
	int currentTime = SDL_GetTicks();
	// calculate framteTime (ms/frame)
	frameTime = currentTime - previousTime;
	// reset frameTimeAverage
	float frameTimeAverage = 0.0f;

	previousTime = currentTime;

	// add new sample
	samples[(index++) % NUMBER_SAMPLES] = frameTime;

	if (index < NUMBER_SAMPLES) {
		count = index;
	}
	else {
		count = NUMBER_SAMPLES;
	}

	// calculate the sum of all samples
	for (int i = 0; i < count; i++) {
		frameTimeAverage = frameTimeAverage + samples[i];
	}

	// calculate the average
	frameTimeAverage = frameTimeAverage / count;

	// calculate the FPS
	if (frameTimeAverage > 0.0f) {
		fps = MILISECONDS / frameTimeAverage;
	}
	else {
		fps = 60.0f;
	}

	// calculate deltaTime
	deltaTime = frameTime / DESIRED_FRAMETIME;
}

void Time::printFPS() {
	if (printMarker == 10) {
		std::cout << "FPS: " << fps << std::endl;
		printMarker = 0;
	}
	else {
		printMarker++;
	}
}

float Time::getDeltaTime() {
	return deltaTime;
}


float Time::getFPS() {
	return fps;
}

float Time::getFrameTime() {
	return frameTime;
}

float Time::getTime() {
	return SDL_GetTicks();
}


