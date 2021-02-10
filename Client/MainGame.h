#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "SDLException.h"
#include "GLSLProgram.h"
#include "ObjectBase.h"
#include "Camera2D.h"
#include "Renderer.h"
#include "ParticleRenderer.h"
#include "InputManager.h"
#include "Player.h"
#include "Block.h"
#include "SpriteBatch.h"
#include "Bullet.h"

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	SDL_Window* window;
	GameState gameState;
	GLSLProgram shaderProgram;
	GLSLProgram geometryProgram;
	GLSLProgram lightProgram;
	Renderer renderer;
	ParticleRenderer particleRenderer;
	Camera2D camera;
	InputManager inputManager;
	Player* player;
	SpriteBatch spriteBatch;
	std::vector<Bullet> bullets;
	float elapsedTime;
	float loopTime;
	float offsetY;
	float fps;
	float frameTime;
	float maxFPS;

public:
	MainGame(int screenWidht, int screenHeight);
	void run();
	void clear();

private:
	void init(int screenWidth, int screenHeight);
	void initWindow(int screenWidht, int screenHeight);
	void initContext();
	void initGlew();
	void initShaders();
	void initPlayer(float x, float y, float width, float height, std::string textureFilePath);
	void initLevel(std::string filePath);
	void drawGrid(int width, int height);
	void setBackgroundColor(float r, float g, float b, float a);
	void initVSYNC();

	void calculateFPS();
	void printFPS(int* t);
	void receiveInput();
	void processInput();
	void drawGame();
	void update();
};

