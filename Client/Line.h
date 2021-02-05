#pragma once
#include "GeometryObject.h"

class Line : public GeometryObject 
{
public:
	Line(float x, float y, float x1, float y1, Color color);
	Line(float x, float y, float x1, float y1, float angle, Color color);

private:
	void init(float x, float y, float x1, float y1, Color color);
	void init(float x, float y, float x1, float y1, float angle, Color color);
	void generateVertecies(float x, float y, float x1, float y1, Color color);
	void generateVertecies(float x, float y, float x1, float y1, float angle, Color color);
};

