#include "MainGame.h"
#include "Config.h"
#include "SDLException.h"
#include "Utils.h"
#include <iostream>

MainGame::MainGame(int screenWidth, int screenHeight) : window(nullptr), gameState(GameState::PLAY), loopTime(5.0f), offsetY(0.0f), elapsedTime(0.0f)
{
	init(screenWidth, screenHeight);
}

void MainGame::init(int screenWidth, int screenHeight)
{
	initWindow(screenWidth, screenHeight);
	initContext();
	initGlew();
	initShaders();
	initPlayer(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_TEXTURE);
	setBackgroundColor(R_CLEAR, G_CLEAR, B_CLEAR, A_CLEAR);
}

void MainGame::initWindow(int screenWidth, int screenHeight)
{
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// create windos
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		throw SDLException(WINDOW_ERROR);
	}
}

void MainGame::initContext()
{
	// initialize context for use with window
	SDL_GLContext glContex = SDL_GL_CreateContext(window);

	if (glContex == nullptr) {
		throw SDLException(CONTEXT_ERROR);
	}
}

void MainGame::initGlew()
{
	// initialize glew
	GLenum error = glewInit();

	if (error != GLEW_OK) {
		throw SDLException(GLEW_ERROR);
	}
}

void MainGame::initShaders() {
	shaderProgram.createProgram();
	shaderProgram.createShaders();
	shaderProgram.compileShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.addAttribute("vertexColor");
	shaderProgram.addAttribute("vertexUV");
	shaderProgram.linkShaders();
}

void MainGame::initPlayer(float x, float y, float width, float height, std::string textureFilePath) {
	player = new ObjectBase(x, y, width, height, textureFilePath);
	enemy = new ObjectBase(-0.5f, -0.5f, 0.25f, 0.25f, textureFilePath);
}

void MainGame::setBackgroundColor(float r, float g, float b, float a)
{
	// every time we call glClead(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	// set background color to one below
	glClearColor(r, g, b, a);
}

void MainGame::run()
{
	while (gameState != GameState::EXIT) {
		processInput();
		update();
		drawGame();
		calculateFPS();
	}

}

void MainGame::update() {
	elapsedTime = SDL_GetTicks() / 1000.0f;

	float x = (cos(elapsedTime) - 1.0f) * 0.5f;
	float y = (sin(elapsedTime) - 1.0f) * 0.5f;

	offsetY = denormalize(y, SCREEN_HEIGHT);

	player->updatePosition(x, y);
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_MOUSEMOTION: {
			std::cout << "X: " << event.motion.x << ", Y: " << event.motion.y << std::endl;
			break;
		}
		default:
			break;
		}
	}
}

void MainGame::drawGame()
{
	// Values specified by glClearDepth are clamped to the range [0,1].
	glClearDepth(1.0f);

	// clear color buffer and depth buffer (after glClearColor is called)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// start rendering
	shaderProgram.use();

	GLint offsetLocation = shaderProgram.getUniformValueLocation("offset");
	GLint offsetYLocation = shaderProgram.getUniformValueLocation("offsetY");
	GLint assetLocation = shaderProgram.getUniformValueLocation("asset");
	//GLint timeLocation = shaderProgram.getUniformValueLocation("time");

	// send value of time variable to GPU
	// 1f means send 1 float
	glUniform2f(offsetLocation, player->getX(), player->getY());
	glUniform1f(offsetYLocation, offsetY);

	// 0 means we are using texture 0
	glUniform1i(assetLocation, 0);
	
	//glUniform1f(timeLocation, elapsedTime);

	player->draw();
	enemy->draw();
	
	// stop rendering
	shaderProgram.unuse();

	// windows A, B ==> B, A <==> render on B and clear A
	SDL_GL_SwapWindow(window);
}

void MainGame::calculateFPS() {
	// static variable are only once initialized
	static const const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	// at the beginning previousTicks are equal to current ticks
	static float previousTicks = SDL_GetTicks();
	static float currentTicks;

	// get current ticks
	currentTicks = SDL_GetTicks();

	// calculate frame time
	frameTime = currentTicks - previousTicks;

	// circular adding of elements to an array
	frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

	// now previous ticks are equal to current ticks after calculation
	previousTicks = currentTicks;

	// number of ticks for calculatinf frameTimeAverage
	int count;

	// if an array is not full set count to  currentFrameTime;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		// else set it to full
		count = NUM_SAMPLES;
	}

	// initialize frameTimeAverage
	float frameTimeAverage = 0;

	// get the sum of samples
	for (int i = 0; i < count; i++) {
		frameTimeAverage = frameTimeAverage + frameTimes[i];
	}

	// calculate the average
	frameTimeAverage = frameTimeAverage / count;

	// calculate the fps
	if (frameTimeAverage > 0) {
		fps = 1000.0f / frameTimeAverage;
	}
	else {
		fps = 60.0f;
	}

	// increase frame index
	currentFrame++;

	std::cout << fps << std::endl;
}
