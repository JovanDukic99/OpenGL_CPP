#pragma once
#include "Graphics.h"
#include <glm/glm.hpp>
class GeometryBase
{
protected:
	glm::vec2 position;
	Color color;
public:
	GeometryBase();
	GeometryBase(glm::vec2 position, Color color);
	GeometryBase(float x, float y, Color color);

	// getters
	glm::vec2 getPosition() const;
	float getX() const;
	float getY() const;
	Color getColor() const;

	// setters
	void setPosition(glm::vec2 position);
	void setPosition(float x, float y);
	void setProperties(glm::vec2 position, Color color);
	void setProperties(float x, float y, Color color);
	void setX(float x);
	void setY(float y);
	void setColor(Color color);
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);
};

