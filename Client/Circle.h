#pragma once
#include "GeometryObject.h"
#include <vector>

class Circle : public GeometryObject
{
public:
	Circle(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertices(float x, float y, float radius, int segments, Color color, std::vector<Vertex>& vertices);
};

