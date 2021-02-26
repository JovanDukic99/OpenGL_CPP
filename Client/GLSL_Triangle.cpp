#include "GLSL_Triangle.h"

GLSL_Triangle::GLSL_Triangle(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_TRIANGLES, 3, offset) {
	init(p1, p2, p3, color, offset, vertices);
}

void GLSL_Triangle::init(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, int& offset, std::vector<Vertex>& vertices) {
	generateVertices(p1, p2, p3, color, vertices);
	updateOffset(offset);
}

void GLSL_Triangle::generateVertices(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const Color& color, std::vector<Vertex>& vertices) {
	// first point
	vertices.emplace_back(p1.x, p1.y, color);
	// second point
	vertices.emplace_back(p2.x, p2.y, color);
	// third point
	vertices.emplace_back(p3.x, p3.y, color);
}
