#include "Light.h"

int Light::nextID = 0;

Light::Light() : ID(nextID++), radius(0), source(0, 0), intensity(1.0f) {

}

Light::Light(int radius, float intensity, glm::vec2 source, Color color) : ID(nextID++), radius(radius), source(source) {
	setSource(source);
	setColor(color);
	setIntensity(intensity);
}

// init
void Light::init(int radius, float intensity, glm::vec2 source, Color color) {
	setRadius(radius);
	setSource(source);
	setColor(color);
	setIntensity(intensity);
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

void Light::setIntensity(float intensity) {
	if (intensity < 0.0f) {
		this->intensity = 1.0f;
	}
	else {
		this->intensity = intensity;
	}
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

Color Light::getColor() const {
	return bounds.getColor();
}

int Light::getID() const {
	return ID;
}

int Light::getRadius() const {
	return radius;
}

float Light::getIntensity() const {
	return intensity;
}

// update
void Light::updateBounds() {
	updateDimensions();
	updatePosition();
}

void Light::updateDimensions() {
	bounds.setDimensions(glm::vec2(2 * radius, 2 * radius));
}

void Light::updatePosition() {
	bounds.setPosition((source - radius * 1.0f));
}

