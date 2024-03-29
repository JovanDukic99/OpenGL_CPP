#pragma once
#include "GLSL_Object.h"
#include <vector>

class GLSL_Square : public GLSL_Object
{
public:
	GLSL_Square(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, float width, float height, Color color, std::vector<Vertex>& vertices);
};

