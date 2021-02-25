#include "Circle.h"

Circle::Circle() : GeometryBase(), radius(0.0f), segments(0) {

}

Circle::Circle(glm::vec2 position, float radius, int segments, Color color) : GeometryBase(position, color), radius(radius), segments(segments) {

}

Circle::Circle(float x, float y, float radius, int segments, Color color) : GeometryBase(x, y, color), radius(radius), segments(segments) {

}

// getters
float Circle::getRadius() const {
	return radius;
}

int Circle::getSegments() const {
	return segments;
}

// setters
void Circle::setProperties(glm::vec2 position, float radius, int segments, Color color) {
	GeometryBase::setProperties(position, color);
	setRadius(radius);
	setSegments(segments);
}

void Circle::setProperties(float x, float y, float radius, int segments, Color color) {
	GeometryBase::setProperties(x, y, color);
	setRadius(radius);
	setSegments(segments);
}

void Circle::setRadius(float radius) {
	this->radius = radius;
}

void Circle::setSegments(int segments) {
	this->segments = segments;
}
