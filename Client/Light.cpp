#include "Light.h"

int Light::nextID = 0;

Light::Light() : ID(nextID++), radius(0), source(0, 0), intensity(0.0f), intensityStep(0.0f), radiusStep(0), maxRadius(0), maxIntensity(0.0f), timer(0), flip(true) {

}

Light::Light(int radius, float intensity, glm::vec2 source, Color color) : ID(nextID++), flip(true), timer(0) {
	init(radius, intensity, source, color);
}

// init
void Light::init(int radius, float intensity, glm::vec2 source, Color color) {
	setRadius(radius);
	setSource(source);
	setColor(color);
	setIntensity(intensity);
	setMaxIntensity(intensity);
	setMaxRadius(radius);
	calculateSteps();
	updateBounds();
}

void Light::calculateSteps() {
	intensityStep = (maxIntensity / (TIME_STEP * MILISECONDS)) * UPDATE_STEP;
	radiusStep = (maxRadius / (TIME_STEP * MILISECONDS)) * UPDATE_STEP;
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

void Light::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	bounds.setColor(r, g, b, a);
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
void Light::update(Uint32 frameTime) {
	// approximately every 5 seconds turn off / on
	timer += frameTime;

	float tempIntensity = 0.0f;
	int tempRadius = 0;

	if (timer >= UPDATE_STEP) {
		if (flip) {
			tempIntensity = intensity - intensityStep;
			tempRadius = radius - radiusStep;
			if (tempIntensity <= 0.0f) {
				if (tempRadius <= 0) {
					setIntensity(0.0f);
					setRadius(0);
					setFlip(false);
				}
				else {
					setRadius(tempRadius);
				}
			}
			else {
				setIntensity(tempIntensity);
				setRadius(tempRadius);
			}
		}
		else {
			tempIntensity = intensity + intensityStep;
			tempRadius = radius + radiusStep;
			if (tempIntensity >= maxIntensity) {
				if (tempRadius >= maxRadius) {
					setIntensity(maxIntensity);
					setRadius(maxRadius);
					setFlip(true);
				}
				else {
					setRadius(tempRadius);
				}
			}
			else {
				setIntensity(tempIntensity);
				setRadius(tempRadius);
			}
		}
		timer = 0;
	}
}

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

void Light::setFlip(bool flip) {
	this->flip = flip;
}

void Light::setMaxRadius(int maxRadius) {
	this->maxRadius = maxRadius;
}

void Light::setMaxIntensity(float maxIntensity) {
	this->maxIntensity = maxIntensity;
}

