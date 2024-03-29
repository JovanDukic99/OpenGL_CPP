#include "Camera2D.h"

Camera2D::Camera2D(float halfWidth, float halfHeight, float cameraX, float cameraY) : halfWidth(halfWidth), halfHeight(halfHeight), position(cameraX, cameraY), cameraMatrix(1.0f), orthoMatrix(1.0f), scale(1.0f), change(true) {
	init();
}

void Camera2D::init() {
	orthoMatrix = glm::ortho((float)-halfWidth, (float)halfWidth, (float)-halfHeight, (float)halfHeight, -1.0f, 1.0f);
	bounds.setProperties(0.0f, 0.0f, 2*halfWidth, 2*halfHeight);
}

void Camera2D::updateOrthoMatrix() {
	orthoMatrix = glm::ortho((float)-halfWidth * scale, (float)halfWidth * scale, (float)-halfHeight * scale, (float)halfHeight * scale, -1.0f, 1.0f);
}

void Camera2D::update() {
	if (change) {
		updateOrthoMatrix();
		updateBounds();

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

bool Camera2D::isBlockInView(float x, float y, float width, float height) {
	return false;
}

void Camera2D::setPosition(const glm::vec2& position) {
	this->position = position;
	setChange(true);
}

void Camera2D::updateBounds() {
	bounds.setPosition(glm::vec2(position.x - halfWidth, position.y - halfHeight));
}

void Camera2D::setDimiension(float halfWidth, float halfHeight) {
	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	setChange(true);
}

void Camera2D::setScale(float scale) {
	this->scale = scale;
	setChange(true);
}

void Camera2D::setChange(bool change) {
	this->change = change;
}

void Camera2D::reset(glm::vec2 position) {
	setScale(1.0f);
	setPosition(position);
}

glm::vec2 Camera2D::getPosition() {
	return position;
}

glm::mat4 Camera2D::getCameraMatrix() {
	return cameraMatrix;
}

glm::mat4& Camera2D::getCameraReference() {
	return cameraMatrix;
}

float Camera2D::getScale() {
	return scale;
}

Square Camera2D::getBounds() const {
	return bounds;
}
