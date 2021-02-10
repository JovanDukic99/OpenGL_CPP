#include "Entity.h"

Entity::Entity(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {

}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}
