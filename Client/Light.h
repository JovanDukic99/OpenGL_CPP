#pragma once
#include "Square.h"
#include <glm/glm.hpp>
#include <vector>
class Light
{
private:
	static int nextID;

	int ID;
	int radius;

	Square bounds;
	glm::vec2 source;
public:
	// constructors
	Light();
	Light(int radius, glm::vec2 source, Color color);

	// init
	void init(int radius, glm::vec2 source, Color color);

	// setters
	void setSource(glm::vec2 source);
	void setColor(Color color);
	void setRadius(int radius);

	// getters
	glm::vec2 getSource() const;
	Square getBounds() const;
	int getID() const;
	int getRadius() const;
private:
	// update
	void updateBounds();
};

