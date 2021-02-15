#include "GLSL_Point.h"

GLSL_Point::GLSL_Point(Point& point, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_POINTS, 1, offset) {
	init(point, offset, vertices);
}

GLSL_Point::GLSL_Point(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_POINTS, 1, offset) {
	init(x, y, color, offset, vertices);
}

void GLSL_Point::init(Point& point, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(point.getX(), point.getY(), point.getColor(), vertices);
	updateOffset(offset);
}

void GLSL_Point::init(float x, float y, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(x, y, color, vertices);
	updateOffset(offset);
}

void GLSL_Point::generateVertecies(float x, float y, Color color, std::vector<Vertex>& vertices) {
	// one point
	vertices.emplace_back(x, y, color);
}

