#pragma once
#include "Square.h"
#include <glm/glm.hpp>
class Light : public Square
{
public:
	// constructors
	Light();
	Light(glm::vec2 position, float width, float height, Color color = WHITE);
	Light(float x, float y, float width, float height, Color color = WHITE);
};

