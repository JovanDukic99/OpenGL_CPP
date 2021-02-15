#include "Square.h"

Square::Square() : GeometryBase(), width(0.0f), height(0.0f) {

}

Square::Square(float x, float y, float width, float height, Color color) : GeometryBase(x, y, color), width(width), height(height) {

}

float Square::getWidth() {
	return width;
}

float Square::getHeight() {
	return height;
}

void Square::setProps(float x, float y, float width, float height) {
	GeometryBase::setPosition(x, y);
	setDimensions(width, height);
}

void Square::setProps(float x, float y, float width, float height, Color color) {
	GeometryBase::setProps(x, y, color);
	setDimensions(width, height);
}

void Square::setDimensions(float width, float height) {
	setWidth(width);
	setHeight(height);
}

void Square::setWidth(float width) {
	this->width = width;
}

void Square::setHeight(float height) {
	this->height = height;
}

