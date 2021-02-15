/*
#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "SDLException.h"
#include "ShaderProgram.h"
#include "ObjectBase.h"
#include "Camera2D.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SpriteBatch.h"
#include "Bullet.h"
#include "FPS.h"

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	SDL_Window* window;
	GameState gameState;
	Renderer* renderer;
	Camera2D camera;
	InputManager inputManager;
	SpriteBatch spriteBatch;
	FPS counter;
	std::vector<Bullet> bullets;
	float maxFPS;
	float imgWidth;
	float imgHeight;

public:
	MainGame(int screenWidht, int screenHeight);
	void run();
	void clear();

private:
	void init(int screenWidth, int screenHeight);
	void initWindow(std::string title, float screenWidth, float screenHeight, Uint32 flags);
	void initShaders();
	void initPlayer(float x, float y, float width, float height, std::string textureFilePath);
	void initLevel(std::string filePath);
	void drawGrid(int width, int height);
	void setBackgroundColor(float r, float g, float b, float a);

	void printFPS(int* t);
	void receiveInput();
	void processInput();
	void drawGame();
	void update();
};
*/

