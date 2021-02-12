#define _USE_MATH_DEFINES
#include "Line.h"
#include <cmath>

Line::Line(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices) : GeometryObject(GL_LINES, 2, offset) {
	init(x, y, x1, y1, color, offset, vertices);
}

void Line::init(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(x, y, x1, y1, color, vertices);
	updateOffset(offset);
}

void Line::generateVertecies(float x, float y, float x1, float y1, Color color, std::vector<Vertex>& vertices) {
	//first point
	vertices.emplace_back(x, y, color);
	// second point
	vertices.emplace_back(x1, y1, color);
}

