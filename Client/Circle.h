#pragma once
#include "GeometryObject.h"
class Circle : public GeometryObject
{
public:
	Circle(float x, float y, float radius, int segments, Color color);
private:
	void init(float x, float y, float radius, int segments, Color color);
	void generateVertices(float x, float y, float radius, int segments, Color color);
};

