#pragma once
#include "GeometryObject.h"
#include <vector>

class Square : public GeometryObject
{
public:
	Square(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices);
private:
	void init(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices);
	void generateVertecies(float x, float y, float width, float height, Color color, std::vector<Vertex>& vertices);
};

