#pragma once
#include "Square.h"
#include <glm/glm.hpp>
#include <vector>
#include <SDL/SDL.h>

#define TIME_STEP 15
#define MILISECONDS 1000.0f
#define UPDATE_STEP 30.0f

class Light
{
private:
	static int nextID;

	int ID;
	int radius;
	int radiusStep;
	float intensity;
	float intensityStep;
	Uint32 timer;
	bool flip;

	int maxRadius;
	float maxIntensity;

	Square bounds;
	glm::vec2 source;
public:
	// constructors
	Light();
	Light(int radius, float intensity, glm::vec2 source, Color color);

	// init
	void init(int radius, float intensity, glm::vec2 source, Color color);
	void calculateSteps();

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

	// update
	void update(Uint32 frameTime);
private:
	// update
	void updateBounds();
	void updateDimensions();
	void updatePosition();

	// setters
	void setFlip(bool flip);
	void setMaxRadius(int maxRadius);
	void setMaxIntensity(float maxIntensity);
};

