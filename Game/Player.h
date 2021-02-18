#pragma once
#include <Square.h>
#include <Point.h>
#include <glm/glm.hpp>
#include <vector>

enum class PlayerState {
	STAND,
	MOVE
};

class Player : public Square
{
private:
	PlayerState playerState;
	glm::vec2 destination;
	glm::vec2 normalizedSpeed;
	std::vector<Point> path; 
	int index;
public:
	Player(float x, float y, float width, float height);
	void update(float deltaTime);
	void setPlayerState(PlayerState playerState);
	void setPath(std::vector<Point> path);
private:
	void setDestination();
	void setNormalizedSpeed();
	void setUp();
	void updatePosition(float deltaTime);
	bool isMoving();
};

