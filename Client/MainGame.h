#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "SDLException.h"
#include "GLSLProgram.h"
#include "ObjectBase.h"

enum class GameState {
	PLAY, EXIT
};

class MainGame
{
private:
	SDL_Window* window;
	GameState gameState;
	GLSLProgram shaderProgram;
	ObjectBase* player;
	float elapsedTime;
	float loopTime;
	float offsetY;

public:
	MainGame(int screenWidht, int screenHeight);
	void run();

private:
	void init(int screenWidth, int screenHeight);
	void initWindow(int screenWidht, int screenHeight);
	void initContext();
	void initGlew();
	void initShaders();
	void initPlayer(float x, float y, float width, float height);
	void setBackgroundColor(float r, float g, float b, float a);

	void processInput();
	void drawGame();
	void update();
};

