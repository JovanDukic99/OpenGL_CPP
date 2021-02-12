#pragma once
#include "GeometryObject.h"
#include <vector>

class Line : public GeometryObject 
{
public:
	Line(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices);

private:
	void init(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, float x1, float y1, Color color, std::vector<Vertex>& vertices);
};

