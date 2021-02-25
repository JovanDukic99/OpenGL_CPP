#pragma once
#include "GeometryBase.h"
#include <glm/glm.hpp>
class Point : public GeometryBase
{
public:
	// constructors
	Point();
	Point(glm::vec2 position, Color color = WHITE);
	Point(float x, float y, Color color = WHITE);
	// operator overloading
	bool operator==(const Point& point);
	bool operator!=(const Point& point);
};

