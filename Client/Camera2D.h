#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Square.h"
class Camera2D
{
private:
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
	Square bounds;
	float scale;
	int halfWidth;
	int halfHeight;
	bool change;
public:
	Camera2D(float halfWidth, float halfHeight, float cameraX, float cameraY);
	glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
	void reset(glm::vec2 position);
	void update();
	bool isBlockInView(float x, float y, float width, float height);
	// setters
	void setPosition(const glm::vec2& position);
	void setDimiension(float halfWidth, float halfHeight);
	void setScale(float scale);
	// getters
	glm::vec2 getPosition();
	glm::mat4 getCameraMatrix();
	glm::mat4& getCameraReference();
	float getScale();
	Square getBounds() const;
private:
	void init();
	void updateOrthoMatrix();
	void updateBounds();
	void setChange(bool change);
};

