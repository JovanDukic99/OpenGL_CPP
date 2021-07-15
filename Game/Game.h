#pragma once
#include <Window.h>
#include <Camera2D.h>
#include <InputManager.h>
#include <ShaderProgram.h>
#include <AStarAlgorithm.h>
#include <Renderer.h>
#include <Square.h>
#include <Point.h>
#include <Light.h>
#include <Edge.h>
#include <SearchSpace.h>
#include <AStarAlgorithm.h>
#include <LightPoint.h>
#include <Animation.h>
#include <TileSheet.h>
#include <TextureAtlas.h>
#include <Block.h>
#include <Timer.h>
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
	TextureAtlas textureAtlas;
	GLTexture bubbleTexture;
	GLTexture atlas;
	Camera2D camera;
	InputManager inputManager;
	Player* player;
	Timer time;
	SearchSpace searchSpace;
	AStarAlgorithm algorithm;
	TileSheet tileSheet;

	std::vector<Block> blocks;
	std::vector<Block> edgeBlocks;
	std::vector<Block> visibleEdgeBlocks;

	std::vector<Square> squarePath;
	std::vector<Light*> lights;

	Light mouseLight;
	Light playerLight;

	int squarePathID;
public:
	Game(std::string title, int screenWidth, int screenHeight);
	~Game();
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
	void updateCamera(float deltaTime);
	void updateLight(Uint32 frameTime);
	void updateWindowState(Uint32 flag);
	void zoom(int zoomY);
	void update(float deltaTime);
	void printFPS();
	void run();
	void draw();
	void drawLights();
	void drawLightArea(std::vector<LightPoint>& intersectionPoints, glm::vec2& visionCenter, Color lightColor);
	void drawGrid();
	void drawEdges(std::vector<Edge*> edges);
	void drawBlocks();
	void drawPlayer();
	void search();
	void reset();
	void updatePlayerPath(std::vector<Point> path);
	void updateSquarePath(std::vector<Point> path);
	bool checkCollision(float x, float y);
	bool cameraCulling(Square square);
	glm::vec2 getCameraPosition(glm::vec2 position);
};

