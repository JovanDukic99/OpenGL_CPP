#include "Camera2D.h"
#include "Config.h"

Camera2D::Camera2D(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), position(0.0f, 0.0f), cameraMatrix(1.0f), orthoMatrix(1.0f), scale(1.0f), change(true)
{
	init();
}

void Camera2D::init() {
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
}

void Camera2D::update() {
	if (change) {
		glm::vec3 translate(-position.x, -position.y, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);

		glm::vec3 scale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(cameraMatrix, scale);
		change = false;
	}
}

void Camera2D::setPosition(const glm::vec2& position) {
	this->position = position;
}

void Camera2D::setScale(float scale) {
	this->scale = scale;
}

void Camera2D::setChange(bool change) {
	this->change = change;
}

glm::vec2 Camera2D::getPosition() {
	return position;
}

glm::mat4 Camera2D::getcameraMatrix() {
	return cameraMatrix;
}

float Camera2D::getScale() {
	return scale;
}
