#include "Circle.h"

Circle::Circle() : GeometryBase(), radius(0.0f), segments(0) {

}

Circle::Circle(float x, float y, float radius, Color color, int segments = SEGMENT_NUMBER) : GeometryBase(x, y, color), radius(radius), segments(segments) {

}

float Circle::getRadius() {
	return radius;
}

int Circle::getSegments() {
	return segments;
}

void Circle::setProps(float x, float y, float radius, int segments) {
	GeometryBase::setPosition(x, y);
	setRadius(radius);
	setSegments(segments);
}

void Circle::setProps(float x, float y, float radius, int segments, Color color) {
	GeometryBase::setProps(x, y, color);
	setRadius(radius);
	setSegments(segments);
}

void Circle::setRadius(float radius) {
	this->radius = radius;
}

void Circle::setSegments(int segments) {
	this->segments = segments;
}
