#pragma once
#include "GeometryBase.h"
class Square : public GeometryBase
{
private:
	glm::vec2 dimensions;
public:
	// constructors
	Square();
	Square(float x, float y, float width, float height, Color color = WHITE);
	Square(glm::vec2 position, float width, float height, Color color = WHITE);
	Square(glm::vec2 position, glm::vec2 dimensions, Color color = WHITE);

	// getters
	float getWidth() const;
	float getHeight() const;
	glm::vec2 getDimensions() const;

	// setters
	void setProperties(glm::vec2 position, float width, float height, Color color = WHITE);
	void setProperties(glm::vec2 position, glm::vec2 dimensions, Color color = WHITE);
	void setProperties(float x, float y, float width, float height, Color color = WHITE);
	void setDimensions(float width, float height);
	void setDimensions(glm::vec2 dimensions);
	void setWidth(float width);
	void setHeight(float height);
};

