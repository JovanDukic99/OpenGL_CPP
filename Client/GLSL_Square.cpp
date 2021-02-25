#include "GLSL_Square.h"

GLSL_Square::GLSL_Square(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_TRIANGLES, 6, offset) {
	init(x, y, width, height, color, offset, vertices);
}

void GLSL_Square::init(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertecies(x, y, width, height, color, vertices);
	updateOffset(offset);
}

void GLSL_Square::generateVertecies(float x, float y, float width, float height, Color color, std::vector<Vertex>& vertices) {
	// top-right corner
	vertices.emplace_back(x + width, y + height, color);
	
	// top-left corner
	vertices.emplace_back(x, y + height, color);

	// bottom-left corner
	vertices.emplace_back(x, y, color);

	// top-right corner
	vertices.emplace_back(x + width, y + height, color);

	// bottom-right corner
	vertices.emplace_back(x + width, y, color);

	// bottom-left corner
	vertices.emplace_back(x, y, color);
}

