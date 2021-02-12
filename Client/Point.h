#pragma once
#include "GeometryObject.h"
#include <vector>

class Point : public GeometryObject
{
public:
	Point(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices);

private:
	void init(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, Color color, std::vector<Vertex>& vertices);
};

