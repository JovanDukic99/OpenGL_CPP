#include"Game.h"
#include "Config.h"
#include <SDLException.h>
#include <iostream>
#include <PriorityQueue.h>

//void print(char* array) {
//	std::cout << array[0];
//}
//
//class Test {
//public:
//	Test() {
//
//	}
//	void operator()(char* array) {
//		std::cout << array[0];
//	}
//};

void test1() {
	Game* game = nullptr;

	try {
		game = new Game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	catch (SDLException e) {
		std::cout << e.message() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	delete game;
}

int main(int argc, char* argv[]) {

	test1();

	/*Game* game = nullptr;

	std::thread t1(test1);
	std::thread t2(&Game::test, game);

	t1.join();
	t2.join();*/

	//void(*foo)(char* array) = print;

	//Test a;

	//Thread<Test, std::string> a(Test(), "a");

	

	return 0;
}

