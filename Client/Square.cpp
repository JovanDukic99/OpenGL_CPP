#include "Square.h"

Square::Square() : GeometryBase(), dimensions(0.0f, 0.0f) {

}

Square::Square(glm::vec2 position, float width, float height, Color color) : GeometryBase(position, color), dimensions(width, height) {

}

Square::Square(glm::vec2 position, glm::vec2 dimensions, Color color) : GeometryBase(position, color), dimensions(dimensions) {

}

Square::Square(float x, float y, float width, float height, Color color) : GeometryBase(x, y, color), dimensions(width, height) {

}

// getters
float Square::getWidth() const {
	return dimensions.x;
}

float Square::getHeight() const {
	return dimensions.y;
}

glm::vec2 Square::getDimensions() const {
	return dimensions;
}

// setters
void Square::setProperties(glm::vec2 position, float width, float height, Color color) {
	GeometryBase::setProperties(position, color);
	setDimensions(width, height);
}

void Square::setProperties(glm::vec2 position, glm::vec2 dimensions, Color color) {
	GeometryBase::setProperties(position, color);
	setDimensions(dimensions);
}

void Square::setProperties(float x, float y, float width, float height, Color color) {
	GeometryBase::setProperties(x, y, color);
	setDimensions(width, height);
}

void Square::setDimensions(float width, float height) {
	setDimensions(glm::vec2(width, height));
}

void Square::setDimensions(glm::vec2 dimensions) {
	this->dimensions = dimensions;
}

void Square::setWidth(float width) {
	setDimensions(glm::vec2(width, getHeight()));
}

void Square::setHeight(float height) {
	setDimensions(glm::vec2(getWidth(), height));
}

