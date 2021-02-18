#include "Player.h"
#include "Config.h"
#include <iostream>

Player::Player(float x, float y, float width, float height) : Square(x, y, width, height), playerState(PlayerState::STAND), destination(0.0f, 0.0f), normalizedSpeed(0.0f, 0.0f), index(0) {

}

void Player::update(float deltaTime) {
	if (isMoving()) {
		if (normalizedSpeed.y >= 0 && normalizedSpeed.x >= 0) {
			if ((getY() < destination.y - 0.1f) || (getX() < destination.x - 0.1f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if (normalizedSpeed.y <= 0 && normalizedSpeed.x <= 0) {
			if ((getY() > destination.y + 0.1f) || (getX() > destination.x + 0.1f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if (normalizedSpeed.y >= 0 && normalizedSpeed.x <= 0) {
			if ((getY() < destination.y - 0.1f) || (getX() > destination.x + 0.1f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if(normalizedSpeed.y <= 0 && normalizedSpeed.x >= 0) {
			if ((getY() > destination.y + 0.1f) || (getX() < destination.x - 0.1f)) {
				updatePosition(deltaTime);
				return;
			}
		}

		if (index < 0) {
			setPlayerState(PlayerState::STAND);
			setPosition(destination.x, destination.y);
			return;
		}

		setDestination();
	}
}

void Player::setPlayerState(PlayerState playerState) {
	this->playerState = playerState;
}

void Player::setDestination() {
	int x = path[index].getX() * UNIT_WIDTH;
	int y = MAP_HEIGHT - (path[index--].getY() * UNIT_HEIGHT) - UNIT_HEIGHT;
	destination = glm::vec2(x, y);
	setNormalizedSpeed();
	std::cout << "X: " << x << ", Y: " << y << std::endl;
}

void Player::setNormalizedSpeed() {
	glm::vec2 vector = destination - glm::vec2(getX(), getY());
	normalizedSpeed = glm::normalize(vector);
}

void Player::setPath(std::vector<Point> path) {
	this->path = path;
	setUp();
}

void Player::setUp() {
	index = path.size() - 1;
	setDestination();
}

void Player::updatePosition(float deltaTime) {
	setPosition(getX() + PLAYER_SPEED * normalizedSpeed.x * deltaTime, getY() + PLAYER_SPEED * normalizedSpeed.y * deltaTime);
	std::cout << "X: " << getX() << ", Y: " << getY() << std::endl;
}

bool Player::isMoving() {
	return playerState == PlayerState::MOVE;
}

