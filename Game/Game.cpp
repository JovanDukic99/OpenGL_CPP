#include "Game.h"
#include "Config.h"
#include <LightPoint.h>
#include <Utils.h>
#include <Light.h>
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
}

void Game::initComponents() {
	player = new Player(START_PLAYER_X, START_PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT);

	camera.setPosition(getCameraPosition(camera.getPosition()));

	bubbleTexture = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterLeft_Jump.png");

	tileSheet.init(bubbleTexture, glm::ivec2(15, 10));

	renderer.init(camera);

	mouseLight.setProperties(START_PLAYER_X, START_PLAYER_Y, 3 * UNIT_WIDTH, 3 * UNIT_HEIGHT);

	lights.emplace_back(&mouseLight);
}

void Game::initLevel(std::string filePath) {
	Utils::loadMASP(filePath, blocks, edgeBlocks, searchSpace, UNIT_WIDTH, UNIT_HEIGHT);
	searchSpace.setMode(Mode::DEFAULT);
	algorithm.setSearchSpace(&searchSpace);

	/*Utils::createEdges(searchSpace, blockEdges, edges, MAP_HEIGHT, UNIT_WIDTH, UNIT_HEIGHT);
	Utils::createEdgePoints(edges, edgePoints);*/
}

void Game::run() {
	while (gameState == GameState::PLAY) {
		calculateFPS();
		printFPS();
		receiveInput();
		processInput();
		update(time.getDeltaTime());
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
	time.calculateFPS();
}

void Game::printFPS() {
	time.printFPS();
}

void Game::updateCameraPosition(int xrel, int yrel) {
	if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		std::cout << "Camera X: " << camera.getPosition().x << ", Camera Y: " << camera.getPosition().y << std::endl;
		camera.setPosition(getCameraPosition(glm::vec2(camera.getPosition().x - xrel, camera.getPosition().y + yrel)));
	}
}

void Game::updatePlayer(float deltaTime) {
	player->update(deltaTime, time.getTime());
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
		camera.reset(getCameraPosition(glm::vec2(player->getX(), player->getY())));
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

void Game::updateLight(float frameTime) {
	glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());

	mouseLight.setPosition(mouseCoords - (mouseLight.getDimensions() / 2.0f));
	mouseLight.setVisionCenter(mouseCoords);
	//playerLight.setPosition(player->getPosition() + (player->getDimensions() / 2.0f) - (light.getDimensions() / 2.0f));
	/*glm::vec2 mouseCoords = camera.convertScreenToWorld(inputManager.getMouseCoords());

	light.setPosition(glm::vec2(mouseCoords.x - 4 * UNIT_WIDTH, mouseCoords.y - 4 * UNIT_HEIGHT));

	return;

	Color color = light.getColor();

	timer += frameTime;

	// approximately every 5 seconds turn off / on
	if (timer >= MILISECONDS * 0.05f) {
		if (flip) {
			alpha = color.a - 2.25f;
			if (alpha <= 0) {
				light.setColor(color.r, color.g, color.b, 0);
				flip = false;
			}
			else {
				light.setColor(color.r, color.g, color.b, alpha);
			}
		}
		else {
			alpha = color.a + 2.25f;
			if (alpha >= 255) {
				light.setColor(color.r, color.g, color.b, 255);
				flip = true;
			}
			else {
				light.setColor(color.r, color.g, color.b, alpha);
			}
		}
		timer = 0.0f;
	} */
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
	return glm::clamp(position, glm::vec2(HALF_WIDTH + UNIT_WIDTH, HALF_HEIGHT + UNIT_HEIGHT), glm::vec2(MAP_WIDTH - HALF_WIDTH - UNIT_WIDTH, MAP_HEIGHT - HALF_HEIGHT - UNIT_HEIGHT));
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
	updateLight(time.getFrameTime());
}

void Game::draw() {
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.begin();

	//renderer.setVision(player->getCenter(), UNIT_WIDTH * 4.0f);

	drawLights();
	drawBlocks();
	drawPlayer();
	drawGrid();

	renderer.drawTexture(*player, player->getTexture());
	renderer.drawTexture(160.0f, 160.0f, 60.0f, 60.0f, bubbleTexture);

	renderer.end();


	SDL_GL_SwapWindow(window);
}

void Game::drawLights() {
	for (size_t i = 0; i < lights.size(); i++) {
		Light* light = lights[i];

		for (size_t i = 0; i < edgeBlocks.size(); i++) {
			Node* edgeBlock = edgeBlocks[i];
			if (Collision::squareCollision(*light, *edgeBlock)) {
				edgeBlock->setVisibility(Visibility::VISIBLE);
				visibleEdges.push_back(edgeBlock);
			}
		}

		glm::vec2 visionCenter = light->getVisionCenter();
		std::vector<glm::vec2> edgePoints;
		std::vector<LightPoint> lightPoints;
		std::vector<Edge*> edges;
		std::vector<LightPoint> intersectionPoints;

		Utils::createEdges(searchSpace, visibleEdges, edges, MAP_HEIGHT, UNIT_WIDTH, UNIT_HEIGHT);
		Utils::createLightEdges(*light, edges);
		Utils::createEdgePoints(edges, edgePoints);
		Utils::rayTracing(edges, edgePoints, intersectionPoints, visionCenter);

		drawLightArea(intersectionPoints, visionCenter);

		for (size_t i = 0; i < visibleEdges.size(); i++) {
			visibleEdges[i]->setVisibility(Visibility::INVISIBLE);
		}

		visibleEdges.clear();
	}
}

void Game::drawLightArea(std::vector<LightPoint>& intersectionPoints, glm::vec2& visionCenter) {
	for (size_t i = 0; i < intersectionPoints.size(); i++) {
		if (i != intersectionPoints.size() - 1) {
			glm::vec2 point1 = intersectionPoints[i].getPosition();
			glm::vec2 point2 = intersectionPoints[i + 1].getPosition();
			renderer.drawLight(visionCenter, point1, point2);
			renderer.drawCircle(point1, 5.0f, 3, RED);
			renderer.drawLine(point1, visionCenter, WHITE);
		}
		else {
			glm::vec2 point1 = intersectionPoints[i].getPosition();
			renderer.drawLight(visionCenter, intersectionPoints[0].getPosition(), point1);
			renderer.drawCircle(point1, 5.0f, 3, YELLOW);
			renderer.drawLine(point1, visionCenter, WHITE);
		}
	}
}

void Game::drawGrid() {
	for (int i = 0; i <= MAP_HORIZONTAL_UNITS; i++) {
		float x = i * UNIT_WIDTH;
		renderer.drawLine(x, 0.0f, x, MAP_HEIGHT, WHITE);
	}

	for (int i = 0; i <= MAP_VERTICAL_UNITS; i++) {
		float y = i * UNIT_HEIGHT;
		renderer.drawLine(0.0f, y, MAP_WIDTH, y, WHITE);
	}

	/*for (size_t i = 0; i < edges.size(); i++) {
		Edge* edge = edges[i];
		renderer.drawLine(*edge, WHITE);
	}*/
}

void Game::drawBlocks() {
	for (size_t i = 0; i < blocks.size(); i++) {
		if (cameraCulling(*blocks[i])) {
			renderer.drawSquare(*blocks[i], GREEN);
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
		if (Collision::squareCollision(square, *blocks[i])) {
			return true;
		}
	}
	return false;
}

bool Game::cameraCulling(Square& square) {
	return Collision::squareCollision(camera.getBounds(), square);
}

