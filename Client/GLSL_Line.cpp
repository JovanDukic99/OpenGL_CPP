#include "GLSL_Line.h"

GLSL_Line::GLSL_Line(const glm::vec2& p1, const glm::vec2& p2, const Color& color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_LINES, 2, offset) {
	init(p1, p2, color, offset, vertices);
}

void GLSL_Line::init(const glm::vec2& p1, const glm::vec2& p2, const Color& color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(p1, p2, color, vertices);
	updateOffset(offset);
}

void GLSL_Line::generateVertecies(const glm::vec2& p1, const glm::vec2& p2, const Color& color, std::vector<Vertex>& vertices) {
	// first point
	vertices.emplace_back(p1.x, p1.y, color);
	// second point
	vertices.emplace_back(p2.x, p2.y, color);
}
