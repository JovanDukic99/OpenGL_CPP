#pragma once
#include "GeometryObject.h"

class Point : public GeometryObject
{
public:
	Point(float x, float y, Color color);

private:
	void init(float x, float y, Color color);
	void generateVertecies(float x, float y, Color color);
};

