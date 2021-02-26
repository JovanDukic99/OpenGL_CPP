#pragma once
#include "Graphics.h"
#include <glm/glm.hpp>
class Triangle
{
private:
	glm::vec2 p1;
	glm::vec2 p2;
	glm::vec2 p3;
	Color color;
public:
	// constructor
	Triangle();
	Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color = WHITE);
	// getters
	glm::vec2 getP1() const;
	glm::vec2 getP2() const;
	glm::vec2 getP3() const;
	Color getColor() const;
	// setters
	void setProperties(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color color = WHITE);
	void setP1(glm::vec2 p1);
	void setP2(glm::vec2 p2);
	void setP3(glm::vec2 p3);
	void setColor(Color color);
};

