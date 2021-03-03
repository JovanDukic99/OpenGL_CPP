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

class Player
{
private:
	enum class MoveDirection {
		NONE,
		LEFT,
		RIGHT
	};
private:
	PlayerState playerState;
	MoveDirection moveDirection;

	glm::vec2 destination;
	glm::vec2 normalizedSpeed;

	size_t index;
	std::vector<Point> path; 

	GLTexture texture;
	Animation animationLeft;
	Animation animationRight;
	Square bounds;

	int* squarePathID;
public:
	// constructor
	Player(float x, float y, float width, float height);

	// update
	void update(float deltaTime, Uint32 time);

	// setters
	void setPlayerState(PlayerState playerState);
	void setPath(std::vector<Point> path, int* squarePathID);

	// getters
	glm::vec2 getCenter() const;
	float getX() const;
	float getY() const;
	GLTexture getTexture() const;
	Square getBounds() const;
private:
	// init
	void init();

	// setters
	void setDestination();
	void setNormalizedSpeed();
	void setUp();
	void setTexture(GLTexture texture);

	// update
	void updatePosition(float deltaTime);

	// getters
	bool isMoving() const;
};

