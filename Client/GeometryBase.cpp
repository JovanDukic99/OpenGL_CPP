#include "GeometryBase.h"

GeometryBase::GeometryBase() : position(0.0f, 0.0f), color() {

}

GeometryBase::GeometryBase(glm::vec2 position, Color color) : position(position), color(color) {

}

GeometryBase::GeometryBase(float x, float y, Color color) : position(x,y), color(color) {

}

// getters
glm::vec2 GeometryBase::getPosition() const {
	return position;
}

float GeometryBase::getX() const {
	return position.x;
}

float GeometryBase::getY() const {
	return position.y;
}

Color GeometryBase::getColor() const {
	return color;
}

void GeometryBase::setPosition(glm::vec2 position) {
	this->position = position;
}

void GeometryBase::setPosition(float x, float y) {
	setPosition(glm::vec2(x, y));
}

// setters
void GeometryBase::setProperties(glm::vec2 position, Color color) {
	setPosition(position);
	setColor(color);
}

void GeometryBase::setProperties(float x, float y, Color color) {
	setPosition(glm::vec2(x, y));
	setColor(color);
}

void GeometryBase::setX(float x) {
	setPosition(glm::vec2(x, position.y));
}

void GeometryBase::setY(float y) {
	setPosition(glm::vec2(position.x, y));
}

void GeometryBase::setColor(Color color) {
	this->color = color;
}

void GeometryBase::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	this->color = Color(r, g, b, a);
}
