#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// scale - for zooming in and out

class Camera2D
{
private:
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;

	float scale;
	int halfWidth;
	int halfHeight;

	bool change;

public:
	Camera2D(float halfWidth, float halfHeight, float cameraX, float cameraY);

	glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

	void reset(float x, float y);
	void update();

	// setters
	void setPosition(const glm::vec2& position);
	void setScale(float scale);

	// getters
	glm::vec2 getPosition();
	glm::mat4 getCameraMatrix();
	float getScale();

private:
	void init();
	void updateOrthoMatrix();
	void setChange(bool change);
};

