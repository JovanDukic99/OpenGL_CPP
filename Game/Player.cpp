#include "Player.h"
#include "Config.h"

Player::Player(float x, float y, float width, float height) : EntityBase(x, y, width, height) {

}

void EntityBase::update(float speedX, float speedY) {
	x = x + speedX;
	y = y + speedY;
}
