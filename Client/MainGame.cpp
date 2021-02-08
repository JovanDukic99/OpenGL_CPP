#include "MainGame.h"
#include "Config.h"
#include "SDLException.h"
#include "Utils.h"
#include <iostream>

MainGame::MainGame(int screenWidth, int screenHeight) : window(nullptr), gameState(GameState::PLAY), camera(screenWidth, screenHeight), loopTime(5.0f), offsetY(0.0f), elapsedTime(0.0f), maxFPS(60.0f)
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
	initVSYNC();
}

void MainGame::initWindow(int screenWidth, int screenHeight)
{
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// create window, use DOUBLEBUFFER window (A, B)
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

	// print OpenGL version
	// we can use this version in vertex, fragment shader
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void MainGame::initShaders() {
	shaderProgram.createProgram();
	shaderProgram.createShaders();
	shaderProgram.compileShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.addAttribute("vertexColor");
	shaderProgram.addAttribute("vertexUV");
	shaderProgram.linkShaders();

	geometryProgram.createProgram();
	geometryProgram.createShaders();
	geometryProgram.compileShaders(OBJECT_VERTEX_PATH, OBJECT_FRAGMENT_PATH);
	geometryProgram.addAttribute("vertexPosition");
	geometryProgram.addAttribute("vertexColor");
	geometryProgram.linkShaders();

	//renderer.drawSquare(0.0f, 0.0f, 60.0f, 60.0f, Color(255, 255, 255, 255));
	//renderer.drawCircle(0.0f, 0.0f, 0.5f, 3, Color(255, 255, 255, 255));

	// vertical grid lines
	for (int i = 0; i <= 18; i++) {
		float x = 60.0f * i;
		renderer.drawLine(x, 0.0f, x, 720.0f, Color(255, 255, 255, 255));
	}

	// vertical grid lines
	for (int i = 0; i <= 12; i++) {
		float y = 60.0f * i;
		renderer.drawLine(0.0f, y, 1080.0f, y, Color(255, 255, 255, 255));
	}

}

void MainGame::initPlayer(float x, float y, float width, float height, std::string textureFilePath) {
	player = new ObjectBase(x, y, width, height, textureFilePath);
}

void MainGame::setBackgroundColor(float r, float g, float b, float a)
{
	// every time we call glClead(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	// set background color to one below
	glClearColor(r, g, b, a);
}

void MainGame::initVSYNC() {
	// set VSYNC to prevent screen tearing (usually occures in 3D games)
	// 1 means on
	SDL_GL_SetSwapInterval(1);
}

void MainGame::run()
{
	int t = 0;
	while (gameState != GameState::EXIT) {
		// used to callculate time of loop execution
		float startTicks = SDL_GetTicks();

		receiveInput();
		processInput();
		update();
		drawGame();
		calculateFPS();

		// print FPS
		t++;
		//printFPS(&t);

		// amount of time to execute while loop
		float frameTicks = SDL_GetTicks() - startTicks;

		// limit the FPS to the max FPS
		if ((1000.f / maxFPS) > frameTicks) {
			// delay execution of while loop
			SDL_Delay((1000.0f / maxFPS) - frameTicks);
		}
	}

}

void MainGame::update() {
	camera.update();
}

void MainGame::receiveInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_MOUSEMOTION: {
			//std::cout << "X: " << event.motion.xrel << ", Y: " << event.motion.yrel << std::endl;
			if (inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
				std::cout << "Camera X: " << camera.getPosition().x << ", Y: " << camera.getPosition().y << std::endl;
				camera.setPosition(glm::vec2(camera.getPosition().x - event.motion.xrel, camera.getPosition().y + event.motion.yrel));
				camera.setChange(true);
			}
			break;
		}
		case SDL_MOUSEWHEEL: {
			if (event.wheel.y > 0) {
				camera.setScale(camera.getScale() + CAMERA_SCALE);

			}
			else {
				camera.setScale(camera.getScale() - CAMERA_SCALE);
			}
			camera.setChange(true);
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

void MainGame::processInput() {
	if (inputManager.isKeyPressed(SDLK_r)) {		
		camera.setScale(1.0f);
		camera.setPosition(glm::vec2(0.0f, 0.0f));
		camera.setChange(true);
	}

	if (inputManager.isKeyPressed(SDLK_q)) {
		
	}

	if (inputManager.isKeyPressed(SDLK_e)) {
		
	}
}

void MainGame::drawGame()
{
	// Values specified by glClearDepth are clamped to the range [0,1].
	glClearDepth(1.0f);

	// clear color buffer and depth buffer (after glClearColor is called)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	geometryProgram.use();

	GLuint orthoLocation = geometryProgram.getUniformValueLocation("cameraMatrix");
	glUniformMatrix4fv(orthoLocation, 1, GL_FALSE, &(camera.getcameraMatrix()[0][0]));

	renderer.render();

	geometryProgram.unuse();

	//// start rendering
	//shaderProgram.use();

	//GLint offsetLocation = shaderProgram.getUniformValueLocation("offset");
	//GLint offsetYLocation = shaderProgram.getUniformValueLocation("offsetY");
	//GLint assetLocation = shaderProgram.getUniformValueLocation("asset");
	////GLint timeLocation = shaderProgram.getUniformValueLocation("time");

	//// send value of time variable to GPU
	//// 1f means send 1 float
	//glUniform2f(offsetLocation, player->getX(), player->getY());
	//glUniform1f(offsetYLocation, offsetY);

	//// 0 means we are using texture 0
	//glUniform1i(assetLocation, 0);
	//
	////glUniform1f(timeLocation, elapsedTime);

	//player->draw();
	//enemy->draw();
	//
	//// stop rendering
	//shaderProgram.unuse();

	// windows A, B ==> B, A <==> render on B and clear A
	SDL_GL_SwapWindow(window);
}

void MainGame::calculateFPS() {
	// static variable are only once initialized
	static const int NUM_SAMPLES = 10;
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

	// increase frame index
	currentFrame++;

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
}

void MainGame::printFPS(int* t) {
	if (*t >= 10) {
		std::cout << "FPS: " << fps << std::endl;
		*t = 0;
	}
}
