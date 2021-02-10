#include <iostream>
#include "MainGame.h"
#include "Config.h"
#include "Socket.h"

int main(int argc, char* argv[]) {

	MainGame* mainGame = nullptr;

	try {
		mainGame = new MainGame(SCREEN_WIDTH, SCREEN_HEIGHT);

		mainGame->run();
	}
	catch (SDLException e) {
		std::cout << e.message() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	mainGame->clear();

	return 0;
}