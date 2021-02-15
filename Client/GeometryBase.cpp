#include "GeometryBase.h"

GeometryBase::GeometryBase() : x(0.0f), y(0.0f), color() {

}

GeometryBase::GeometryBase(float x, float y, Color color) : x(x), y(y), color(color) {

}

// getters
float GeometryBase::getX() {
	return x;
}

float GeometryBase::getY() {
	return y;
}

Color GeometryBase::getColor() {
	return color;
}

void GeometryBase::setPosition(float x, float y) {
	setX(x);
	setY(y);
}

// setters
void GeometryBase::setProps(float x, float y, Color color) {
	setX(x);
	setY(y);
	setColor(color);
}

void GeometryBase::setX(float x) {
	this->x = x;
}

void GeometryBase::setY(float y) {
	this->y = y;
}

void GeometryBase::setColor(Color color) {
	this->color = color;
}
