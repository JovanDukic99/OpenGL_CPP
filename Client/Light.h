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
	float intensity;

	Square bounds;
	glm::vec2 source;
public:
	// constructors
	Light();
	Light(int radius, float intensity, glm::vec2 source, Color color);

	// init
	void init(int radius, float intensity, glm::vec2 source, Color color);

	// setters
	void setSource(glm::vec2 source);
	void setColor(Color color);
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);
	void setRadius(int radius);
	void setIntensity(float intensity);

	// getters
	glm::vec2 getSource() const;
	Square getBounds() const;
	Color getColor() const;
	int getID() const;
	int getRadius() const;
	float getIntensity() const;
private:
	// update
	void updateBounds();
	void updateDimensions();
	void updatePosition();
};

