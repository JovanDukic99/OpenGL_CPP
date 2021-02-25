#include "Square.h"

Square::Square() : GeometryBase(), width(0.0f), height(0.0f) {

}

Square::Square(glm::vec2 position, float width, float height, Color color) : GeometryBase(position, color), width(width), height(height) {

}

Square::Square(float x, float y, float width, float height, Color color) : GeometryBase(x, y, color), width(width), height(height) {

}

// getters
float Square::getWidth() const {
	return width;
}

float Square::getHeight() const {
	return height;
}

// setters
void Square::setProperties(glm::vec2 position, float width, float height, Color color) {
	GeometryBase::setProperties(position, color);
	setDimensions(width, height);
}

void Square::setProperties(float x, float y, float width, float height, Color color) {
	GeometryBase::setProperties(x, y, color);
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

