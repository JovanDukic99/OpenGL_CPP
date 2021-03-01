#include "Light.h"

Light::Light() : Square(), visionCenter(0.0f, 0.0f) {

}

Light::Light(glm::vec2 position, float width, float height, Color color) : Square(position, width, height, color), visionCenter(0.0f, 0.0f) {

}

Light::Light(float x, float y, float width, float height, Color color) : Square(x, y, width, height, color), visionCenter(0.0f, 0.0f) {

}

// setters
void Light::setVisionCenter(glm::vec2 visionCenter) {
	this->visionCenter = visionCenter;
}

// getters
glm::vec2 Light::getVisionCenter() const {
	return visionCenter;
}