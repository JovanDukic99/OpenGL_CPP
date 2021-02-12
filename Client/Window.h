#pragma once
#include <SDL/SDL.h>
#include <string>

class Window
{
private:
	static SDL_Window* window;
public:
	static SDL_Window* init(std::string title, int screenWidth, int screenHeight, Uint32 flags);
private:
	static void initWindow(std::string title, int screenWidth, int screenHeight, Uint32 flags);
	static void initContex();
	static void initGlew();
	static void initVSync();
};

