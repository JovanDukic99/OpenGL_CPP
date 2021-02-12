#pragma once
class EntityBase
{
private:
	float x;
	float y;
	float width;
	float height;
public:
	EntityBase(float x, float y, float width, float height);

	// gettets
	float getX();
	float getY();

	float getWidth();
	float getHeight();

	// setters
	void update(float x, float y);
};

