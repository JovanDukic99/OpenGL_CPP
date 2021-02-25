#include "GLSL_Point.h"

GLSL_Point::GLSL_Point(const glm::vec2& p, const Color& color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_POINTS, 1, offset) {
	init(p, color, offset, vertices);
}

void GLSL_Point::init(const glm::vec2& p, const Color& color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(p, color, vertices);
	updateOffset(offset);
}

void GLSL_Point::generateVertecies(const glm::vec2& p, const Color& color, std::vector<Vertex>& vertices) {
	// one point
	vertices.emplace_back(p.x, p.y, color);
}

