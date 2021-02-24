#pragma once
#include <Square.h>
#include <Point.h>
#include <glm/glm.hpp>
#include <Animation.h>
#include <vector>

enum class PlayerState {
	STAND,
	MOVE
};

enum class MoveDirection {
	NONE,
	LEFT,
	RIGHT
};

class Player : public Square
{
private:
	PlayerState playerState;
	MoveDirection moveDirection;
	glm::vec2 destination;
	glm::vec2 normalizedSpeed;
	std::vector<Point> path; 
	size_t index;
	Animation animationLeft;
	Animation animationRight;
	GLTexture texture;
public:
	Player(float x, float y, float width, float height);
	void update(float deltaTime, Uint32 time);
	void setPlayerState(PlayerState playerState);
	void setPath(std::vector<Point> path);
	Point getCenter();
	GLTexture getTexture();
private:
	void init();
	void setDestination();
	void setNormalizedSpeed();
	void setUp();
	void setTexture(GLTexture texture);
	void updatePosition(float deltaTime);
	bool isMoving();
};

