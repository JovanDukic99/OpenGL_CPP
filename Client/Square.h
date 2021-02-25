#pragma once
#include "GeometryBase.h"
class Square : public GeometryBase
{
private:
	float width;
	float height;
public:
	// constructors
	Square();
	Square(float x, float y, float width, float height, Color color = WHITE);
	Square(glm::vec2 position, float width, float height, Color color = WHITE);

	// getters
	float getWidth() const;
	float getHeight() const;

	// setters
	void setProperties(glm::vec2 position, float width, float height, Color color = WHITE);
	void setProperties(float x, float y, float width, float height, Color color = WHITE);
	void setDimensions(float width, float height);
	void setWidth(float width);
	void setHeight(float height);
};

