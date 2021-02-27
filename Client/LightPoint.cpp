#include "LightPoint.h"

LightPoint::LightPoint(glm::vec2 position, float angle) : position(position), angle(angle) {

}

// getters
glm::vec2 LightPoint::getPosition() const {
	return position;
}

float LightPoint::getAngle() const {
	return angle;
}
