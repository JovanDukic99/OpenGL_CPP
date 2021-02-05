#pragma once
#include "GeometryObject.h"

class Square : public GeometryObject
{
public:
	Square(float x, float y, float width, float height, Color color);
	Square(float x, float y, float width, float height, float angle, Color color);
private:
	void init(float x, float y, float width, float height, Color color);
	void init(float x, float y, float width, float height, float angle, Color color);
	void generateVertecies(float x, float y, float width, float height, Color color);
	void generateVertecies(float x, float y, float width, float height, float angle, Color color);
};

