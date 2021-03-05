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
	renderer.setMode(RenderMode::SHADOWS);

	mouseLight.init(10 * UNIT_WIDTH, 1.0f, glm::vec2(160, 160), RED);
	playerLight.init(20 * UNIT_WIDTH, 1.0f, glm::vec2(START_PLAYER_X, START_PLAYER_Y), BLUE);

	squarePathID = -1;

	lights.emplace_back(&playerLight);
	lights.emplace_back(&mouseLight);
}

void Game::initLevel(std::string filePath) {
	Utils::loadMSPL(filePath, lights, blocks, edgeBlocks, searchSpace, UNIT_WIDTH, UNIT_HEIGHT);
	algorithm.setSearchSpace(&searchSpace);
	renderer.setLights(lights);
}

void Game::run() {
	while (gameState == GameState::PLAY) {
		calculateFPS();
		printFPS();
		receiveInput();
		processInput();
		update(time.getDeltaTime());
		draw();
		//reset();
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

void Game::reset() {
	
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
	mouseLight.setSource(camera.convertScreenToWorld(inputManager.getMouseCoords()));
	playerLight.setSource(player->getCenter());

	float intensity = mouseLight.getIntensity();
	int radius = mouseLight.getRadius();


	timer += frameTime;

	// approximately every 5 seconds turn off / on
	if (timer >= MILISECONDS * 0.05f) {
		if (flip) {
			intensity = intensity - 0.01f;
			radius = radius - 6;
			if (intensity <= 0) {
				mouseLight.setIntensity(0.0f);
				mouseLight.setRadius(0);
				flip = false;
			}
			else {
				mouseLight.setIntensity(intensity);
				mouseLight.setRadius(radius);
			}
		}
		else {
			intensity = intensity + 0.01f;
			radius = radius + 6;
			if (intensity >= 1.0f) {
				mouseLight.setIntensity(1.0f);
				mouseLight.setRadius(10 * UNIT_WIDTH);
				flip = true;
			}
			else {
				mouseLight.setIntensity(intensity);
				mouseLight.setRadius(radius);
			}
		}
		timer = 0.0f;
	}
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

	drawBlocks();
	drawPlayer();
	drawLights();
	//drawGrid();

	//renderer.drawTexture(player->getBounds(), player->getTexture());
	//renderer.drawTexture(160.0f, 160.0f, 60.0f, 60.0f, bubbleTexture);

	renderer.end();

	SDL_GL_SwapWindow(window);
}

void Game::drawLights() {
	for (size_t i = 0; i < lights.size(); i++) {
		Light* light = lights[i];

		if (!cameraCulling(light->getBounds())) {
			continue;
		}

		renderer.drawLight(light);

		for (size_t i = 0; i < edgeBlocks.size(); i++) {
			Block edgeBlock = edgeBlocks[i];
			if (Collision::squareCollision(light->getBounds(), edgeBlock.getBounds())) {
				glm::ivec2 matrixPosition = edgeBlock.getMatrixPosition();
				searchSpace.setVisibility(matrixPosition.y, matrixPosition.x, Visibility::VISIBLE);
				visibleEdgeBlocks.push_back(edgeBlock);
			}
		}

		glm::vec2 lightSource = light->getSource();
		std::vector<glm::vec2> edgePoints;
		std::vector<LightPoint> lightPoints;
		std::vector<Edge*> edges;
		std::vector<LightPoint> intersectionPoints;

		Utils::createEdges(searchSpace, visibleEdgeBlocks, edges, MAP_HEIGHT, UNIT_WIDTH, UNIT_HEIGHT);
		Utils::createLightEdges(light, edges);
		Utils::createEdgePoints(light, edges, edgePoints);
		Utils::rayTracing(edges, edgePoints, intersectionPoints, lightSource);

		drawLightArea(intersectionPoints, lightSource, light->getColor());

		for (size_t i = 0; i < visibleEdgeBlocks.size(); i++) {
			Block edgeBlock = visibleEdgeBlocks[i];
			glm::ivec2 matrixPosition = edgeBlock.getMatrixPosition();
			searchSpace.setVisibility(matrixPosition.y, matrixPosition.x, Visibility::INVISIBLE);
		}

		//drawEdges(edges);

		visibleEdgeBlocks.clear();
	}
}

void Game::drawLightArea(std::vector<LightPoint>& intersectionPoints, glm::vec2& visionCenter, Color lightColor) {
	for (size_t i = 0; i < intersectionPoints.size(); i++) {
		if (i != intersectionPoints.size() - 1) {
			glm::vec2 point1 = intersectionPoints[i].getPosition();
			glm::vec2 point2 = intersectionPoints[i + 1].getPosition();
			renderer.drawLightMask(visionCenter, point1, point2, lightColor);
			//renderer.drawCircle(point1, 5.0f, 3, RED);
			//renderer.drawLine(point1, visionCenter, WHITE);
		}
		else {
			glm::vec2 point1 = intersectionPoints[i].getPosition();
			renderer.drawLightMask(visionCenter, intersectionPoints[0].getPosition(), point1, lightColor);
			//renderer.drawCircle(point1, 5.0f, 3, YELLOW);
			//renderer.drawLine(point1, visionCenter, WHITE);
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
}

void Game::drawEdges(std::vector<Edge*> edges) {
	for (size_t i = 0; i < edges.size(); i++) {
		Edge* edge = edges[i];
		renderer.drawLine(edge->getEdge(), YELLOW);
	}
}

void Game::drawBlocks() {
	for (size_t i = 0; i < lights.size(); i++) {
		Light* light = lights[i];
		if (!cameraCulling(light->getBounds())) {
			continue;
		}
		for (size_t j = 0; j < blocks.size(); j++) {
			Block block = blocks[j];

			if (Collision::squareCollision(light->getBounds(), block.getBounds())) {
				renderer.drawSquare(light, block.getBounds(), GREEN);
			}
		}
	}

	/*for (size_t i = 0; i < blocks.size(); i++) {
		if (cameraCulling(blocks[i].getBounds())) {
			renderer.drawSquare(blocks[i].getBounds(), GREEN);
		}
	}*/

	/*if (squarePathID != -1) {
		for (size_t i = squarePathID; i < squarePath.size(); i++) {
			if (i == squarePath.size() - 1) {
				renderer.drawSquare(squarePath[squarePath.size() - 1], RED);
			}
			else {
				renderer.drawSquare(squarePath[i]);
			}
		}
	}*/
}

void Game::drawPlayer() {
	if (Collision::squareCollision(mouseLight.getBounds(), player->getBounds())) {
		renderer.drawSquare(&mouseLight, player->getBounds(), BLUE);
	}
	renderer.drawSquare(&playerLight, player->getBounds(), BLUE);
	renderer.drawTexture(&playerLight, player->getBounds(), player->getTexture());
}

void Game::updatePlayerPath(std::vector<Point> playerPath) {
	player->setPath(playerPath, &squarePathID);
	player->setPlayerState(PlayerState::MOVE);
}

void Game::updateSquarePath(std::vector<Point> path) {
	squarePathID = 0;
	squarePath.clear();
	for (size_t i = 0; i < path.size(); i++) {
		Point point = path[i];
		squarePath.emplace_back(point.getX(), point.getY(), UNIT_WIDTH, UNIT_HEIGHT, YELLOW);
	}
}

bool Game::checkCollision(float x, float y) {
	Square square(player->getBounds());
	for (size_t i = 0; i < blocks.size(); i++) {
		if (Collision::squareCollision(square, blocks[i].getBounds())) {
			return true;
		}
	}
	return false;
}

bool Game::cameraCulling(Square square) {
	return Collision::squareCollision(camera.getBounds(), square);
}

