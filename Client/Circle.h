#pragma once
#include "GeometryBase.h"
#include <glm/glm.hpp>

#define SEGMENT_NUMBER 20

class Circle : public GeometryBase
{
private:
	float radius;
	int segments;
public:
	// constructors
	Circle();
	Circle(glm::vec2 position, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);
	Circle(float x, float y, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);

	// getters
	float getRadius() const;
	int getSegments() const;

	// setters
	void setProperties(glm::vec2 position, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);
	void setProperties(float x, float y, float radius, int segments = SEGMENT_NUMBER, Color color = WHITE);
	void setRadius(float radius);
	void setSegments(int segments);
};

