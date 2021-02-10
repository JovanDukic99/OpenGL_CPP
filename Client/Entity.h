#pragma once
class Entity
{
private:
	float x;
	float y;
	float width;
	float height;

public:
	Entity(float x, float y, float width, float height);
	
	// setters
	virtual void update(float x, float y);
	
	// getters
	float getX();
	float getY();
	float getWidth();
	float getHeight();
};

