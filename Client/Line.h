#pragma once
#include "Graphics.h"
class Line
{
private:
	float points[4];
	Color color;
public:
	Line();
	Line(float x, float y, float x1, float y1, Color color);

	// getters
	float* getPoints();
	Color getColor();

	// setters
	void setPoints(float x, float y, float x1, float y1);
	void setPoints(float x, float y, float x1, float y1, Color color);
	void setColor(Color color);
};

