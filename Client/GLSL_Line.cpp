#include "GLSL_Line.h"

GLSL_Line::GLSL_Line(Line& line, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_LINES, 2, offset) {
	init(line, offset, vertices);
}

GLSL_Line::GLSL_Line(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_LINES, 2, offset) {
	init(x, y, x1, y1, color, offset, vertices);
}

void GLSL_Line::init(Line& line, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(line.getPoints(), line.getColor(), vertices);
	updateOffset(offset);
}

void GLSL_Line::init(float x, float y, float x1, float y1, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(x, y, x1, y1, color, vertices);
	updateOffset(offset);
}

void GLSL_Line::generateVertecies(float* points, Color color, std::vector<Vertex>& vertices) {
	//first point
	vertices.emplace_back(points[0], points[1], color);
	// second point
	vertices.emplace_back(points[2], points[3], color);
}

void GLSL_Line::generateVertecies(float x, float y, float x1, float y1, Color color, std::vector<Vertex>& vertices) {
	//first point
	vertices.emplace_back(x, y, color);
	// second point
	vertices.emplace_back(x1, y1, color);
}

