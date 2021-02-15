/*
#include "MainGame.h"
#include "EngineConfig.h"
#include "SDLException.h"
#include "Utils.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include "Window.h"
#include <iostream>

MainGame::MainGame(int screenWidth, int screenHeight) : window(nullptr), gameState(GameState::PLAY), camera(HALF_WIDTH, HALF_HEIGHT, HALF_WIDTH, HALF_HEIGHT), maxFPS(60.0f)
{
	init(screenWidth, screenHeight);
}

void MainGame::init(int screenWidth, int screenHeight)
{
	initWindow("XD", screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	initPlayer(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_TEXTURE);
	initShaders();
	initLevel(LEVEL_PATH);
	setBackgroundColor(R_CLEAR, G_CLEAR, B_CLEAR, A_CLEAR);
}

void MainGame::initWindow(std::string title, float screenWidth, float screenHeight, Uint32 flags) {
	window = Window::init(title, screenWidth, screenHeight, flags);
}

void MainGame::initShaders() {
	// print OpenGL version
	// we can use this version in vertex, fragment shader
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	/*geometryProgram.createProgram();
	geometryProgram.createShaders();
	geometryProgram.compileShaders(OBJECT_VERTEX_PATH, OBJECT_FRAGMENT_PATH);
	geometryProgram.addAttribute("vertexPosition");
	geometryProgram.addAttribute("vertexColor");
	geometryProgram.linkShaders();

	lightProgram.createProgram();
	lightProgram.createShaders();
	lightProgram.compileShaders(LIGHT_VERTEX_PATH, LIGHT_FRAGMENT_PATH);
	lightProgram.addAttribute("vertexPosition");
	lightProgram.addAttribute("vertexColor");
	lightProgram.linkShaders();
}

void MainGame::initPlayer(float x, float y, float width, float height, std::string textureFilePath) {
	renderer = new Renderer();
	spriteBatch.init();
}

void MainGame::initLevel(std::string filePath) {
	Image image = ImageLoader::loadImage(filePath);

	for (int i = 0; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			int pixel = image[i][j];
			int r = (pixel >> 24) & 0xff;
			int g = (pixel >> 16) & 0xff;
			int b = (pixel >> 8) & 0xff;
			int a = pixel & 0xff;

			int x = j * BLOCK_WIDTH;
			int y = 2*SCREEN_HEIGHT - (i * BLOCK_HEIGHT) - BLOCK_HEIGHT;

			if((r == 0) && (g == 0) && (b == 0) && (a == 255)) {

			}
		}
	}

	imgWidth = image.getWidth();
	imgHeight = image.getHeight();

	image.clear();
}

void MainGame::drawGrid(int width, int height) {
	// vertical grid lines
	for (int i = 0; i <= width; i++) {
		float x = UNIT_WIDTH * i;
		renderer->drawLine(x, 0.0f, x, 2 * SCREEN_HEIGHT, Color(255, 255, 255, 255));
	}

	// horizontal grid lines
	for (int i = 0; i <= height; i++) {
		float y = UNIT_HEIGHT * i;
		renderer->drawLine(0.0f, y, 2 * SCREEN_WIDTH, y, Color(255, 255, 255, 255));
	}
}

void MainGame::setBackgroundColor(float r, float g, float b, float a)
{
	// every time we call glClead(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	// set background color to one below
	glClearColor(r, g, b, a);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void MainGame::run()
{
	int t = 0;
	while (gameState != GameState::EXIT) {
		// used to callculate time of loop execution
		float startTicks = SDL_GetTicks();

		receiveInput();
		processInput();
		update();
		drawGame();
		counter.calculateFPS();

		// print FPS
		t++;
		printFPS(&t);

		// amount of time to execute while loop
		float frameTicks = SDL_GetTicks() - startTicks;

		// limit the FPS to the max FPS
		if ((1000.f / maxFPS) > frameTicks) {
			// delay execution of while loop
			SDL_Delay((1000.0f / maxFPS) - frameTicks);
		}
	}

}

void MainGame::update() {
	camera.update();
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].update();
	}
}

void MainGame::receiveInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_MOUSEMOTION: {
			//std::cout << "X: " << event.motion.x << ", Y: " << event.motion.y << std::endl;
			inputManager.setMouseCoords(glm::vec2(event.motion.x, SCREEN_HEIGHT - event.motion.y));
			if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
				std::cout << "Camera X: " << camera.getPosition().x << ", Camera Y: " << camera.getPosition().y << std::endl;
				camera.setPosition(glm::vec2(camera.getPosition().x - event.motion.xrel, camera.getPosition().y + event.motion.yrel));
			}
			break;
		}
		case SDL_MOUSEWHEEL: {
			if (event.wheel.y > 0) {
				camera.setScale(camera.getScale() - CAMERA_SCALE);

			}else {
				camera.setScale(camera.getScale() + CAMERA_SCALE);
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			inputManager.pressKey(event.button.button);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			inputManager.releaseKey(event.button.button);
			break;
		}
		case SDL_KEYDOWN: {
			inputManager.pressKey(event.key.keysym.sym);
			break;
		}
		case SDL_KEYUP: {
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		}
		default:
			break;
		}
	}
}

void MainGame::processInput() {
	if (inputManager.isKeyPressed(SDLK_r)) {		
		camera.setScale(1.0f);
		camera.setPosition(glm::vec2(HALF_WIDTH, HALF_HEIGHT));
	}

	if (inputManager.isKeyPressed(SDLK_a)) {
		//player->update(player->getX() - PLAYER_SPEED, player->getY());
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		//player->update(player->getX() + PLAYER_SPEED, player->getY());
	}

	if (inputManager.isKeyPressed(SDLK_w)) {
		//player->update(player->getX(), player->getY() + PLAYER_SPEED);
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		//player->update(player->getX(), player->getY() - PLAYER_SPEED);
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());
		std::cout << "x: " << mouseCoords.x << ", y: " << mouseCoords.y << std::endl;
	
		glm::vec2 playerPosition(120.0f, 120.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		bullets.emplace_back(playerPosition, direction, 1.0f, PLAYER_TEXTURE);
	}
}

void MainGame::drawGame()
{
	// Values specified by glClearDepth are clamped to the range [0,1].
	glClearDepth(1.0f);

	// clear color buffer and depth buffer (after glClearColor is called)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// geometry program
	//geometryProgram.use();

	//GLuint location = geometryProgram.getUniformValueLocation("cameraMatrix");
	//glUniformMatrix4fv(location, 1, GL_FALSE, &(camera.getCameraMatrix()[0][0]));

	renderer->begin();

	/*for (int i = 0; i < blocks.size(); i++) {
		Block block = blocks[i];
		renderer->drawSquare(block.getX(), block.getY(), block.getWidth(), block.getHeight(), Color(0, 255, 0, 255));
	}

	drawGrid(imgWidth, imgHeight);

	renderer->end();

	//geometryProgram.unuse();

	// windows A, B ==> B, A <==> render on B and clear A
	SDL_GL_SwapWindow(window);
}

void MainGame::printFPS(int* t) {
	if (*t >= 10) {
		std::cout << "FPS: " << counter.getFPS() << std::endl;
		*t = 0;
	}
}

void MainGame::clear() {
	/*if (player != nullptr) {
		delete player;
		delete renderer;
	}
}

*/
