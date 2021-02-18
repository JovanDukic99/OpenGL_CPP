#include"Game.h"
#include "Config.h"
#include <SDLException.h>
#include <iostream>
#include <PriorityQueue.h>

int main(int argc, char* argv[]) {

	Game* game = nullptr;

	try {
		game = new Game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	catch (SDLException e) {
		std::cout << e.message() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	game->clear();

	delete game;

	return 0;
}

