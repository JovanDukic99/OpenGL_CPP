#include "Camera2D.h"

Camera2D::Camera2D(float halfWidth, float halfHeight, float cameraX, float cameraY) : halfWidth(halfWidth), halfHeight(halfHeight), position(cameraX, cameraY), cameraMatrix(1.0f), orthoMatrix(1.0f), scale(1.0f), change(true) {
	init();
}

void Camera2D::init() {
	orthoMatrix = glm::ortho((float)-halfWidth, (float)halfWidth, (float)-halfHeight, (float)halfHeight, -1.0f, 1.0f);
	position = glm::clamp(position, glm::vec2(halfWidth, halfHeight), glm::vec2(3 * halfWidth, 3 * halfHeight));
}

void Camera2D::updateOrthoMatrix() {
	orthoMatrix = glm::ortho((float)-halfWidth * scale, (float)halfWidth * scale, (float)-halfHeight * scale, (float)halfHeight * scale, -1.0f, 1.0f);
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
	screenCoords = screenCoords - glm::vec2(halfWidth, halfHeight);

	// scale the coordinates
	screenCoords = screenCoords * scale;

	// translate with the camera position
	screenCoords = screenCoords + position;

	return screenCoords;
}

void Camera2D::setPosition(const glm::vec2& position) {
	this->position = glm::clamp(position, glm::vec2(halfWidth, halfHeight), glm::vec2(3 * halfWidth, 3  *halfHeight));
	setChange(true);
}

void Camera2D::setScale(float scale) {
	this->scale = scale;
	setChange(true);
}

void Camera2D::setChange(bool change) {
	this->change = change;
}

void Camera2D::reset(float x, float y) {
	scale = 1.0f;
	setPosition(glm::vec2(x, y));
}

glm::vec2 Camera2D::getPosition() {
	return position;
}

glm::mat4 Camera2D::getCameraMatrix() {
	return cameraMatrix;
}

float Camera2D::getScale() {
	return scale;
}
