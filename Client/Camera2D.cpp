#include "Camera2D.h"
#include "Config.h"

Camera2D::Camera2D(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), position((float) HALF_WIDTH, (float) HALF_HEIGHT), cameraMatrix(1.0f), orthoMatrix(1.0f), scale(1.0f), change(true)
{
	init();
}

void Camera2D::init() {
	orthoMatrix = glm::ortho((float)-HALF_WIDTH, (float)HALF_WIDTH, (float)-HALF_HEIGHT, (float)HALF_HEIGHT, -1.0f, 1.0f);
}

void Camera2D::updateOrthoMatrix() {
	orthoMatrix = glm::ortho((float)-HALF_WIDTH * scale, (float)HALF_WIDTH * scale, (float)-HALF_HEIGHT * scale, (float)HALF_HEIGHT * scale, -1.0f, 1.0f);
}

void Camera2D::update() {
	if (change) {
		updateOrthoMatrix();

		glm::vec3 translate(-position.x, -position.y, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);

		change = false;
	}
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
	// make (0, 0) center of screen
	screenCoords = screenCoords - glm::vec2(screenWidth / 2, screenHeight / 2);

	// scale the coordinates
	screenCoords = screenCoords / scale;

	// translate with the camera position
	screenCoords = screenCoords + position;

	return screenCoords;
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
