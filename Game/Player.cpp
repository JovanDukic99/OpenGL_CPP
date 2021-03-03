#include "Player.h"
#include "Config.h"
#include <ResourceManager.h>
#include <iostream>

Player::Player(float x, float y, float width, float height) : bounds(x, y, width, height), playerState(PlayerState::STAND), moveDirection(MoveDirection::NONE), destination(0.0f, 0.0f), normalizedSpeed(0.0f, 0.0f), index(0) {
	init();
}

void Player::init() {
	GLTexture texture1 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	GLTexture texture2 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Walk1.png");
	GLTexture texture3 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Walk2.png");

	animationRight.addTexture(texture1);
	animationRight.addTexture(texture2);
	animationRight.addTexture(texture3);
	animationRight.setFrameTime(200);

	texture1 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterLeft_Standing.png");
	texture2 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterLeft_Walk1.png");
	texture3 = ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterLeft_Walk2.png");

	animationLeft.addTexture(texture1);
	animationLeft.addTexture(texture2);
	animationLeft.addTexture(texture3);
	animationLeft.setFrameTime(200);

	setTexture(texture1);
}

void Player::update(float deltaTime, Uint32 time) {
	if (isMoving()) {

		if (moveDirection == MoveDirection::RIGHT) {
			setTexture(animationRight.getTexture(time));
		}
		else {
			setTexture(animationLeft.getTexture(time));
		}

		if (normalizedSpeed.y >= 0 && normalizedSpeed.x >= 0) {
			if ((bounds.getY() < destination.y - 0.01f) || (bounds.getX() < destination.x - 0.01f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if (normalizedSpeed.y <= 0 && normalizedSpeed.x <= 0) {
			if ((bounds.getY() > destination.y + 0.01f) || (bounds.getX() > destination.x + 0.01f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if (normalizedSpeed.y >= 0 && normalizedSpeed.x <= 0) {
			if ((bounds.getY() < destination.y - 0.01f) || (bounds.getX() > destination.x + 0.01f)) {
				updatePosition(deltaTime);
				return;
			}
		}
		else if(normalizedSpeed.y <= 0 && normalizedSpeed.x >= 0) {
			if ((bounds.getY() > destination.y + 0.01f) || (bounds.getX() < destination.x - 0.01f)) {
				updatePosition(deltaTime);
				return;
			}
		}

		if (index >= path.size()) {
			setPlayerState(PlayerState::STAND);
			bounds.setPosition(destination.x, destination.y);
			(*squarePathID) = -1;
			return;
		}

		(*squarePathID)++;

		setDestination();
	}
}

void Player::setPlayerState(PlayerState playerState) {
	this->playerState = playerState;
}

void Player::setDestination() {
	int x = path[index].getX();
	int y = path[index++].getY();;
	destination = glm::vec2(x, y);
	setNormalizedSpeed();
	//std::cout << "Destination X: " << x << ", Destination Y: " << y << std::endl;
}

void Player::setNormalizedSpeed() {
	glm::vec2 vector = destination - glm::vec2(bounds.getX(), bounds.getY());
	normalizedSpeed = glm::normalize(vector);
}

void Player::setPath(std::vector<Point> path, int* squarePathID) {
	this->path = path;
	this->squarePathID = squarePathID;
	setUp();
}

Square Player::getBounds() const {
	return bounds;
}

glm::vec2 Player::getCenter() const {
	return glm::vec2(bounds.getX() + bounds.getWidth() / 2.0f, bounds.getY() + bounds.getHeight() / 2.0f);
}

float Player::getX() const {
	return bounds.getX();
}

float Player::getY() const {
	return bounds.getY();
}

void Player::setUp() {
	index = 0;

	Point finalPoint = path[path.size() - 1];

	if (finalPoint.getX() > bounds.getX()) {
		moveDirection = MoveDirection::RIGHT;
	}
	else if (finalPoint.getX() < bounds.getX()) {
		moveDirection = MoveDirection::LEFT;
	}

	setDestination();
}

void Player::setTexture(GLTexture texture) {
	this->texture = texture;
}

void Player::updatePosition(float deltaTime) {
	bounds.setPosition(bounds.getX() + PLAYER_SPEED * normalizedSpeed.x * deltaTime, bounds.getY() + PLAYER_SPEED * normalizedSpeed.y * deltaTime);
	//std::cout << "X: " << getX() << ", Y: " << getY() << std::endl;
}

bool Player::isMoving() const {
	return playerState == PlayerState::MOVE;
}

GLTexture Player::getTexture() const {
	return texture;
}

