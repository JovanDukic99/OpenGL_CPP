#include "Game.h"
#include "Config.h"
#include <Utils.h>
#include <ResourceManager.h>
#include <Collision.h>
#include <GL/glew.h>
#include <iostream>
#include <thread>

Game::Game(std::string title, int screenWidth, int screenHeight) : gameState(GameState::PLAY), windowState(WindowState::MAXIMIZED), renderer(), camera(HALF_WIDTH, HALF_HEIGHT, START_PLAYER_X, START_PLAYER_Y), searchSpace() {
	init(title, screenWidth, screenHeight);
}

Game::~Game() {
	delete player;
}

void Game::init(std::string title, int screenWidth, int screenHeight) {
	initWindow(title, screenWidth, screenHeight);
	initBackgroundProps(CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
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

void Game::initComponents() {
	player = new Player(START_PLAYER_X, START_PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
	camera.setPosition(getCameraPosition(camera.getPosition()));
	texture = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	bubbleTexture = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterLeft_Jump.png");
	renderer.init(camera);
}

void Game::initLevel(std::string filePath) {
	Utils::loadMASP(filePath, blocks, searchSpace, UNIT_WIDTH, UNIT_HEIGHT);
	algorithm.setSearchSpace(&searchSpace);
}

void Game::run() {
	while (gameState == GameState::PLAY) {
		calculateFPS();
		receiveInput();
		processInput();
		update(fpsCounter.getDeltaTime());
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
			case SDL_WINDOWEVENT: {
				updateWindowState(event.window.event);
				break;
			}
			default: {
				break;
			}
		}
	}
}

void Game::processInput() {
	if (inputManager.isKeyPressed(SDLK_r)) {
		camera.reset(getCameraPosition(glm::vec2(player->getX(), player->getY())));
	}

	if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
		gameState = GameState::EXIT;
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		inputManager.releaseKey(SDL_BUTTON_RIGHT);
		if (!algorithm.isSearching()) {
			std::thread(&Game::search, this).detach();
		}
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());
		std::cout << "Mouse X: " << mouseCoords.x << ", Mouse Y: " << mouseCoords.y << std::endl;
	}
}

void Game::search() {
	std::cout << std::endl;

	glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());

	std::cout << "Mouse X: " << mouseCoords.x << ", Mouse Y: " << mouseCoords.y << std::endl;
	std::cout << "Player X: " << player->getX() << ", Player Y: " << player->getY() << std::endl;

	int endX = (int)(mouseCoords.x / UNIT_WIDTH);
	int endY = (int)(MAP_VERTICAL_UNITS - (mouseCoords.y / UNIT_HEIGHT));

	std::cout << "End X: " << endX << ", End Y: " << endY << std::endl;

	int startX = (int)(player->getX() / UNIT_WIDTH);
	int startY = (int)(MAP_VERTICAL_UNITS - (player->getY()) / UNIT_HEIGHT - 1);

	std::cout << "Start X: " << startX << ", Start Y: " << startY << std::endl;
	
	if (!searchSpace.setStartNode(startY, startX)) {
		std::cout << "Start node is a block." << std::endl;
		return;
	}

	if (!searchSpace.setFinalNode(endY, endX)) {
		std::cout << "End node is a block." << std::endl;
		return;
	}

	SearchResult result = algorithm.search();

	if (result == FOUND) {
		std::cout << "Path has been found." << std::endl;
		std::vector<Point> path = Utils::convertToSquarePath(Utils::reverse(searchSpace.getPath()), MAP_HEIGHT, UNIT_WIDTH, UNIT_HEIGHT);
		updateSquarePath(path);
		updatePlayerPath(path);
	}
	else if (result == ALREADY_FOUND) {
		std::cout << "Path has been already found." << std::endl;
	}
	else {
		std::cout << "No path has been found." << std::endl;
	}

	algorithm.reset();
}

void Game::calculateFPS() {
	fpsCounter.calculateFPS();
}

void Game::printFPS() {
	fpsCounter.printFPS();
}

void Game::updateCameraPosition(int xrel, int yrel) {
	if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		std::cout << "Camera X: " << camera.getPosition().x << ", Camera Y: " << camera.getPosition().y << std::endl;
		camera.setPosition(getCameraPosition(glm::vec2(camera.getPosition().x - xrel, camera.getPosition().y + yrel)));
	}
}

void Game::updatePlayer(float deltaTime) {
	player->update(deltaTime);
	/*if (inputManager.isKeyPressed(SDLK_a)) {
		if (!checkCollision(player->getX() - PLAYER_SPEED * deltaTime, player->getY())) {
			player->update(-PLAYER_SPEED, 0.0f, deltaTime);
			camera.setPosition(getCameraPosition(glm::vec2(player->getX(), player->getY())));
		}
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		if (!checkCollision(player->getX() + PLAYER_SPEED * deltaTime, player->getY())) {
			player->update(PLAYER_SPEED, 0.0f, deltaTime);
			camera.setPosition((getCameraPosition(glm::vec2(player->getX(), player->getY()))));
		}
	}

	if (inputManager.isKeyPressed(SDLK_w)) {
		if (!checkCollision(player->getX(), player->getY() + PLAYER_SPEED * deltaTime)) {
			player->update(0.0f, PLAYER_SPEED, deltaTime);
			camera.setPosition(getCameraPosition(glm::vec2(player->getX(), player->getY())));
		}
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		if (!checkCollision(player->getX(), player->getY() - PLAYER_SPEED * deltaTime)) {
			player->update(0.0f, -PLAYER_SPEED, deltaTime);
			camera.setPosition((getCameraPosition(glm::vec2(player->getX(), player->getY()))));
		}
	}*/
}

void Game::updateCamera(float deltaTime) {
	if (inputManager.isKeyPressed(SDLK_SPACE)) {
		camera.setPosition(getCameraPosition(glm::vec2(player->getX(), player->getY())));
		camera.update();
		return;
	}
	//camera.setPosition(getCameraPosition(glm::vec2(player->getX(), player->getY())));
	glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());
	glm::vec2 cameraCoords = camera.getPosition();

	if (mouseCoords.x >= cameraCoords.x + HALF_WIDTH - CAMERA_MOVE_OFFSET_HORIZONTAL) {
		camera.setPosition(getCameraPosition(glm::vec2(cameraCoords.x + CAMERA_SPEED * deltaTime, cameraCoords.y)));
	}else if (mouseCoords.x <= cameraCoords.x - HALF_WIDTH + CAMERA_MOVE_OFFSET_HORIZONTAL) {
		camera.setPosition(getCameraPosition(glm::vec2(cameraCoords.x - CAMERA_SPEED * deltaTime, cameraCoords.y)));
	}

	cameraCoords = camera.getPosition();

	if (mouseCoords.y >= cameraCoords.y + HALF_HEIGHT - CAMERA_MOVE_OFFSET_VERTICAL) {
		camera.setPosition(getCameraPosition(glm::vec2(cameraCoords.x, cameraCoords.y + CAMERA_SPEED * deltaTime)));
	}
	else if (mouseCoords.y <= cameraCoords.y - HALF_HEIGHT + CAMERA_MOVE_OFFSET_VERTICAL) {
		camera.setPosition(getCameraPosition(glm::vec2(cameraCoords.x, cameraCoords.y - CAMERA_SPEED * deltaTime)));
	}

	camera.update();
}

void Game::updateWindowState(Uint32 flag) {
	if (flag == SDL_WINDOWEVENT_FOCUS_LOST) {
		if (windowState == WindowState::MAXIMIZED) {
			SDL_MinimizeWindow(window);
			windowState = WindowState::MINIMIZED;
		}
	}
	else if (flag == SDL_WINDOWEVENT_FOCUS_GAINED) {
		windowState = WindowState::MAXIMIZED;
	}
}

glm::vec2 Game::getCameraPosition(glm::vec2 position) {
	return glm::clamp(position, glm::vec2(HALF_WIDTH, HALF_HEIGHT), glm::vec2(MAP_WIDTH - HALF_WIDTH, MAP_HEIGHT - HALF_HEIGHT));
}

void Game::zoom(int zoomY) {
	if (zoomY > 0) {
		camera.setScale(camera.getScale() - SCALE_FACTOR);
	}
	else {
		camera.setScale(camera.getScale() + SCALE_FACTOR);
	}
}

void Game::update(float deltaTime) {
	int i = 0;
	while (deltaTime > 0.0f && i < MAX_STEPS) {
		float time = glm::min(deltaTime, 1.0f);
		updatePlayer(time);
		updateCamera(time);
		deltaTime -= time;
		i++;
	}
}

void Game::draw() {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.begin();

	drawBlocks();
	drawPlayer();
	drawGrid();

	renderer.drawTexture(*player, texture);
	renderer.drawTexture(160.0f, 160.0f, 60.0f, 60.0f, bubbleTexture);

	renderer.end();

	SDL_GL_SwapWindow(window);
}

void Game::drawLights() {

}

void Game::drawGrid() {
	for (int i = 0; i <= 2 * VERTICAL_UNITS; i++) {
		float x = i * UNIT_WIDTH;
		renderer.drawLine(x, 0.0f, x, 2 * SCREEN_HEIGHT, WHITE);
	}

	for (int i = 0; i <= 2 * HORIZONTAL_UNITS; i++) {
		float y = i * UNIT_HEIGHT;
		renderer.drawLine(0.0f, y, 2 * SCREEN_WIDTH, y, WHITE);
	}
}

void Game::drawBlocks() {
	for (size_t i = 0; i < blocks.size(); i++) {
		if (cameraCulling(blocks[i])) {
			renderer.drawSquare(blocks[i], GREEN);
		}
	}

	if (!squarePath.empty()) {
		renderer.drawSquare(squarePath[0], RED);
		for (size_t i = 1; i < squarePath.size() - 1; i++) {
			renderer.drawSquare(squarePath[i]);
		}
		renderer.drawSquare(squarePath[squarePath.size() - 1], VIOLET);
	}
}

void Game::drawPlayer() {
	renderer.drawSquare(*player, BLUE);
}

void Game::updatePlayerPath(std::vector<Point> playerPath) {
	player->setPath(playerPath);
	player->setPlayerState(PlayerState::MOVE);
}

void Game::updateSquarePath(std::vector<Point> path) {
	squarePath.clear();
	for (size_t i = 0; i < path.size(); i++) {
		Point point = path[i];
		squarePath.emplace_back(point.getX(), point.getY(), UNIT_WIDTH, UNIT_HEIGHT, YELLOW);
	}
}

bool Game::checkCollision(float x, float y) {
	Square square(x, y, player->getWidth(), player->getHeight());
	for (size_t i = 0; i < blocks.size(); i++) {
		if (Collision::squareCollision(square, blocks[i])) {
			return true;
		}
	}
	return false;
}

bool Game::cameraCulling(Square& square) {
	return Collision::squareCollision(camera.getBounds(), square);
}

