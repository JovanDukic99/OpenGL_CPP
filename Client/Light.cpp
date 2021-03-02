#include "Light.h"

int Light::nextID = 0;

Light::Light() : ID(nextID++), radius(0), source(0, 0) {

}

Light::Light(int radius, glm::vec2 source, Color color) : ID(nextID++), radius(radius), source(source) {
	setSource(source);
	setColor(color);
}

// init
void Light::init(int radius, glm::vec2 source, Color color) {
	setRadius(radius);
	setSource(source);
	setColor(color);
	updateBounds();
}

// setters
void Light::setSource(glm::vec2 source) {
	this->source = source;
	updateBounds();
}

void Light::setRadius(int radius) {
	this->radius = radius;
	updateBounds();
}

void Light::setColor(Color color) {
	bounds.setColor(color);
}

// getters
glm::vec2 Light::getSource() const {
	return source;
}

Square Light::getBounds() const {
	return bounds;
}

int Light::getID() const {
	return ID;
}

int Light::getRadius() const {
	return radius;
}

// update
void Light::updateBounds() {
	bounds.setProperties((source - radius * 1.0f), glm::vec2(2 * radius, 2 * radius));
}

