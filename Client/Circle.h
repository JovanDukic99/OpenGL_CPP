#pragma once
#include "GeometryBase.h"
#define SEGMENT_NUMBER 60
class Circle : public GeometryBase
{
private:
	float radius;
	int segments;
public:
	Circle();
	Circle(float x, float y, float radius, Color color, int segments);

	// getters
	float getRadius();
	int getSegments();

	// setters
	void setProps(float x, float y, float radius, int segments);
	void setProps(float x, float y, float radius, int segments, Color color);
	void setRadius(float radius);
	void setSegments(int segments);
};

