#include "Game.h"
#include "Config.h"
#include "Utils.h"
#include <GL/glew.h>
#include <iostream>

Game::Game(std::string title, int screenWidth, int screenHeight) : gameState(GameState::PLAY), camera(HALF_WIDTH, HALF_HEIGHT, START_PLAYER_X, START_PLAYER_Y) {
	init(title, screenWidth, screenHeight);
}

void Game::init(std::string title, int screenWidth, int screenHeight) {
	initWindow(title, screenWidth, screenHeight);
	initBackgroundProps(CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
	initShaders();
	initComponents();
	initLevel(MAP_PATH);
	run();
}

void Game::initWindow(std::string title, int screenWidth, int screenHeight) {
	window = Window::init(title, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
}

void Game::initBackgroundProps(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initShaders() {
	shaderProgram.createProgram();
	shaderProgram.createShaders();
	shaderProgram.compileShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.addAttribute("vertexColor");
	shaderProgram.linkShaders();
}

void Game::initComponents() {
	player = new Player(START_PLAYER_X, START_PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
	renderer = new Renderer();
}

void Game::initLevel(std::string filePath) {
	Utils::loadMap(filePath, blocks);
}

void Game::run() {
	while (gameState == GameState::PLAY) {
		receiveInput();
		processInput();
		update();
		draw();
	}
}

void Game::receiveInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_MOUSEMOTION: {
			inputManager.setMouseCoords(glm::vec2(event.motion.x, SCREEN_HEIGHT - event.motion.y));
			updateCameraPosition(event.motion.xrel, event.motion.yrel);
			break;
		}
		case SDL_MOUSEWHEEL: {
			zoom(event.wheel.y);
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

void Game::processInput() {
	if (inputManager.isKeyPressed(SDLK_r)) {
		camera.reset(player->getX(), player->getY());
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());
		std::cout << "Mouse X: " << mouseCoords.x << ", Mouse Y: " << mouseCoords.y << std::endl;
	}
}

void Game::updateCameraPosition(int xrel, int yrel) {
	if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		std::cout << "Camera X: " << camera.getPosition().x << ", Camera Y: " << camera.getPosition().y << std::endl;
		camera.setPosition(glm::vec2(camera.getPosition().x - xrel, camera.getPosition().y + yrel));
	}	
}

void Game::updatePlayer() {
	if (inputManager.isKeyPressed(SDLK_a)) {
		if (!checkCollision(player->getX() - PLAYER_SPEED, player->getY())) {
			player->update(-PLAYER_SPEED, 0.0f);
			camera.setPosition(glm::vec2(player->getX(), player->getY()));
		}
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		if (!checkCollision(player->getX() + PLAYER_SPEED, player->getY())) {
			player->update(PLAYER_SPEED, 0.0f);
			camera.setPosition(glm::vec2(player->getX(), player->getY()));
		}
	}

	if (inputManager.isKeyPressed(SDLK_w)) {
		if (!checkCollision(player->getX(), player->getY() + PLAYER_SPEED)) {
			player->update(0.0f, PLAYER_SPEED);
			camera.setPosition(glm::vec2(player->getX(), player->getY()));
		}
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		if (!checkCollision(player->getX(), player->getY() - PLAYER_SPEED)) {
			player->update(0.0f, -PLAYER_SPEED);
			camera.setPosition(glm::vec2(player->getX(), player->getY()));
		}
	}
}

void Game::zoom(int zoomY) {
	if (zoomY > 0) {
		camera.setScale(camera.getScale() - SCALE_FACTOR);
	}
	else {
		camera.setScale(camera.getScale() + SCALE_FACTOR);
	}
}

void Game::update() {
	updatePlayer();
	camera.update();
}

void Game::draw() {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.use();

	GLuint location = shaderProgram.getUniformValueLocation("cameraMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &(camera.getCameraMatrix()[0][0]));

	renderer->begin();

	drawBlocks();
	drawPlayer();
	drawGrid();

	renderer->end();

	shaderProgram.unuse();

	SDL_GL_SwapWindow(window);
}

void Game::drawGrid() {
	for (int i = 0; i <= 2 * VERTICAL_UNITS; i++) {
		float x = i * UNIT_WIDTH;
		renderer->drawLine(x, 0.0f, x, 2 * SCREEN_HEIGHT, Color(255, 255, 255, 255));
	}

	for (int i = 0; i <= 2 * HORIZONTAL_UNITS; i++) {
		float y = i * UNIT_HEIGHT;
		renderer->drawLine(0.0f, y, 2 * SCREEN_WIDTH, y, Color(255, 255, 255, 255));
	}
}

void Game::drawBlocks() {
	for (int i = 0; i < blocks.size(); i++) {
		Block block = blocks[i];
		renderer->drawSquare(block.getX(), block.getY(), block.getWidth(), block.getHeight(), Color(0, 255, 0, 255));
	}
}

void Game::drawPlayer() {
	renderer->drawSquare(player->getX(), player->getY(), player->getWidth(), player->getHeight(), Color(0, 0, 255, 255));
}

bool Game::checkCollision(float x, float y) {
	Block block(x, y, player->getWidth(), player->getHeight());
	for (int i = 0; i < blocks.size(); i++) {
		if (Utils::squareCollision(block, blocks[i])) {
			return true;
		}
		else if (Utils::squareCollision(blocks[i], block)) {
			return true;
		}
	}
	return false;
}

void Game::clear() {
	delete player;
	delete renderer;
}

