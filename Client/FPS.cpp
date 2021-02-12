#include "FPS.h"
#include <SDL/SDL.h>

FPS::FPS() : index(0), count(0), samples(), previousTime(0), fps(0.0f) {

}

void FPS::calculateFPS() {
	// get current time
	int currentTime = SDL_GetTicks();
	// calculate framteTime (ms/frame)
	int frameTime = currentTime - previousTime;
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
}

float FPS::getFPS() {
	return fps;
}
