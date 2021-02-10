#include "Player.h"

Player::Player(float x, float y, float width, float height) : Entity(x, y, width, height) {

}

void Entity::update(float x, float y) {
	this->x = x;
	this->y = y;
}
