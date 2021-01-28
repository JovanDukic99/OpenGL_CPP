#include <Socket.h>
#include <iostream>
#include "MainGame.h"
#include "Config.h"

int main(int argc, char* argv[]) {

	try {
		MainGame* mainGame = new MainGame(SCREEN_WIDTH, SCREEN_HEIGHT);

		mainGame->run();
	}
	catch (SDLException e) {
		std::cout << e.message() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	return 0;
}