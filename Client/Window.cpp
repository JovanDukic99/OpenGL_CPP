#include "Window.h"
#include "SDLException.h"
#include <GL/glew.h>

SDL_Window* Window::window = nullptr;

SDL_Window* Window::init(std::string title, int width, int height, Uint32 flags) {
	initWindow(title, width, height, flags);
	initContex();
	initGlew();
	initVSync();
	return window;
}

void Window::initWindow(std::string title, int width, int height, Uint32 flags) {
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// create window, use DOUBLEBUFFER window (A, B)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (window == nullptr) {
		throw SDLException(WINDOW_ERROR);
	}
}

void Window::initContex() {
	// initialize context for use with window
	SDL_GLContext glContex = SDL_GL_CreateContext(window);

	if (glContex == nullptr) {
		throw SDLException(CONTEXT_ERROR);
	}
}

void Window::initGlew() {
	// initialize glew
	GLenum error = glewInit();

	if (error != GLEW_OK) {
		throw SDLException(GLEW_ERROR);
	}
}

void Window::initVSync() {
	// set VSYNC to prevent screen tearing (usually occures in 3D games)
	// 1 means on
	SDL_GL_SetSwapInterval(1);
}
