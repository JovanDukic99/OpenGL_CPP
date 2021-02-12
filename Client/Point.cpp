#include "Point.h"

Point::Point(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices) : GeometryObject(GL_POINTS, 1, offset) {
	init(x, y, color, offset, vertices);
}

void Point::init(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(x, y, color, vertices);
	updateOffset(offset);
}

void Point::generateVertecies(float x, float y, Color color, std::vector<Vertex>& vertices) {
	// one point
	vertices.emplace_back(x, y, color);
}

