#pragma once
#include "GLSL_Object.h"
#include "Line.h"
#include <vector>

class GLSL_Line : public GLSL_Object
{
public:
	GLSL_Line(Line& line, int& offset, std::vector<Vertex>& vertices);
	GLSL_Line(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices);

private:
	void init(Line& line, int& offset, std::vector<Vertex>& vertices);
	void init(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float* points, Color color, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, float x1, float y1, Color color, std::vector<Vertex>& vertices);
};

