#pragma once
#include "GeometryBase.h"
class Square : public GeometryBase
{
private:
	float width;
	float height;
public:
	Square();
	Square(float x, float y, float width, float height, Color color = WHITE);

	// getters
	float getWidth();
	float getHeight();

	// setters
	void setProps(float x, float y, float width, float height);
	void setProps(float x, float y, float width, float height, Color color);
	void setDimensions(float width, float height);
	void setWidth(float width);
	void setHeight(float height);
};

