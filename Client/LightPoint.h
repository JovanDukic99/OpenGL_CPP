#pragma once
#include <glm/glm.hpp>
class LightPoint
{
private:
	glm::vec2 position;
	float angle;
public:
	// constructor
	LightPoint(glm::vec2 position, float angle);
	// getters
	glm::vec2 getPosition() const;
	float getAngle() const;
};

