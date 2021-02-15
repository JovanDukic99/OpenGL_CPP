#pragma once
#include "GLSL_Object.h"
#include "Point.h"
#include <vector>

class GLSL_Point : public GLSL_Object
{
public:
	GLSL_Point(Point& point, int& offset, std::vector<Vertex>& vertices);
	GLSL_Point(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices);

private:
	void init(Point& point, int& offset, std::vector<Vertex>& vertices);
	void init(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, Color color, std::vector<Vertex>& vertices);
};

