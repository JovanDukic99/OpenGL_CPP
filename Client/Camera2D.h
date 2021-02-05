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
	bool change;
	float scale;
	int screenWidth;
	int screenHeight;

public:
	Camera2D(int screenWidth, int screenHeight);
	void update();

	// setters
	void setPosition(const glm::vec2& position);
	void secScale(float scale);

	// getters
	glm::vec2 getPosition();
	glm::mat4 getcameraMatrix();
	float getScale();

private:
	void init();
};

