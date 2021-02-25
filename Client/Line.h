#pragma once
#include "Graphics.h"
#include "Point.h"
#include <glm/glm.hpp>

class Line
{
private:
	Color color;
	glm::vec2 p1;
	glm::vec2 p2;
public:
	// constructors
	Line();
	Line(glm::vec2 p1, glm::vec2 p2, Color color = WHITE);
	Line(float x, float y, float x1, float y1, Color color = WHITE);

	// helper
	bool contains(glm::vec2 point);

	// getters
	Color getColor();
	glm::vec2 getP1();
	glm::vec2 getP2();

	// setters
	void setProperties(glm::vec2 p1, glm::vec2 p2, Color color = WHITE);
	void setProperties(float x, float y, float x1, float y1, Color color = WHITE);
	void setP1(glm::vec2 p1);
	void setP2(glm::vec2 p2);
	void setColor(Color color);

};

