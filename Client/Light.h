#pragma once
#include "Square.h"
#include <glm/glm.hpp>
class Light : public Square
{
private:
	int intensity;
	glm::vec2 visionCenter;
public:
	// constructors
	Light();
	Light(glm::vec2 position, float width, float height, Color color = WHITE);
	Light(float x, float y, float width, float height, Color color = WHITE);
	// setters
	void setVisionCenter(glm::vec2 visionCenter);
	// getters
	glm::vec2 getVisionCenter() const;
};

