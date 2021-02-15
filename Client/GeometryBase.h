#pragma once
#include "Graphics.h"
class GeometryBase
{
private:
	float x;
	float y;
	Color color;
public:
	GeometryBase();
	GeometryBase(float x, float y, Color color);

	// getters
	float getX();
	float getY();
	Color getColor();

	// setters
	void setPosition(float x, float y);
	void setProps(float x, float y, Color color);
	void setX(float x);
	void setY(float y);
	void setColor(Color color);
};

