#pragma once
#include <Window.h>
#include <Camera2D.h>
#include <InputManager.h>
#include <ShaderProgram.h>
#include <AStarAlgorithm.h>
#include <Renderer.h>
#include <Square.h>
#include <Point.h>
#include <FPS.h>
#include <string>
#include <vector>
#include "Player.h"

enum class GameState {
	PLAY,
	EXIT
};

enum class WindowState {
	MAXIMIZED,
	MINIMIZED
};

class Game
{
private:
	SDL_Window* window;
	Renderer renderer;
	GameState gameState;
	WindowState windowState;
	AStarAlgorithm algorithm;
	GLTexture texture;
	GLTexture bubbleTexture;
	Camera2D camera;
	InputManager inputManager;
	FPS fpsCounter;
	Player* player;
	std::vector<Square> blocks;
	std::vector<Square> squarePath;

public:
	Game(std::string title, int screenWidth, int screenHeight);
	void clear();
private:
	void init(std::string title, int screenWidth, int screenHeight);
	void initWindow(std::string title, int screenWidth, int screenHeight);
	void initBackgroundProps(float r, float g, float b, float a);
	void initComponents();
	void initLevel(std::string filePath);
	void receiveInput();
	void processInput();
	void calculateFPS();
	void updateCameraPosition(int xrel, int yrel);
	void updatePlayer(float deltaTime);
	void updateCamera();
	void updateWindowState(Uint32 flag);
	void zoom(int zoomY);
	void update(float deltaTime);
	void printFPS();
	void run();
	void draw();
	void drawLights();
	void drawGrid();
	void drawBlocks();
	void drawPlayer();
	void createPath(std::vector<Point> path);
	bool checkCollision(float x, float y);
	bool cameraCulling(Square& square);
	glm::vec2 getCameraPosition(glm::vec2 position);
};

