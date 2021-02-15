#include "Player.h"
#include "Config.h"

Player::Player(float x, float y, float width, float height) : Square(x, y, width, height) {

}

void Player::update(float x, float y, float deltaTime) {
	setPosition(getX() + x * deltaTime, getY() + y * deltaTime);
}

