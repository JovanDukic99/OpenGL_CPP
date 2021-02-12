#pragma once
#include <Window.h>
#include <Camera2D.h>
#include <Renderer.h>
#include <InputManager.h>
#include <ShaderProgram.h>
#include <string>
#include <vector>
#include "Block.h"
#include "Player.h"

enum class GameState {
	PLAY,
	EXIT
};

class Game
{
private:
	SDL_Window* window;
	Renderer* renderer;
	ShaderProgram shaderProgram;
	GameState gameState;
	Camera2D camera;
	InputManager inputManager;
	Player* player;
	std::vector<Block> blocks;
public:
	Game(std::string title, int screenWidth, int screenHeight);
	void clear();
private:
	void init(std::string title, int screenWidth, int screenHeight);
	void initWindow(std::string title, int screenWidth, int screenHeight);
	void initBackgroundProps(float r, float g, float b, float a);
	void initShaders();
	void initComponents();
	void initLevel(std::string filePath);
	void receiveInput();
	void processInput();
	void updateCameraPosition(int xrel, int yrel);
	void updatePlayer();
	void zoom(int zoomY);
	void update();
	void run();
	void draw();
	void drawGrid();
	void drawBlocks();
	void drawPlayer();
	bool checkCollision(float x, float y);
};

