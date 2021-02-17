#include"Game.h"
#include "Config.h"
#include <SDLException.h>
#include <iostream>
#include <LinkedList.h>

int main(int argc, char* argv[]) {

	LinkedList<int> list;

	for (int i = 0; i < 5; i++) {
		list.add(i + 1);
	}

	for (int i = 0; i < list.size(); i++) {
		std::cout << list[i] << ", ";
	}

	std::cout << std::endl;

	list.remove(5);

	for (int i = 0; i < list.size(); i++) {
		std::cout << list[i] << ", ";
	}

	std::cout << list.last();

	list.clear();


	/*Game* game = nullptr;

	try {
		game = new Game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	catch (SDLException e) {
		std::cout << e.message() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	game->clear();

	delete game;*/

	return 0;
}