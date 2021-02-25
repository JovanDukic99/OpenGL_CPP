#pragma once
#include "GLSL_Object.h"
#include <vector>

class GLSL_Circle : public GLSL_Object
{
public:
	GLSL_Circle(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertices(float x, float y, float radius, int segments, Color color, std::vector<Vertex>& vertices);
};

