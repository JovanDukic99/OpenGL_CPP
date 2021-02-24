#include "GLSL_Light.h"

GLSL_Light::GLSL_Light(Light& light, int& offset, std::vector<Vertex>& lightVertices) : GLSL_Object(GL_TRIANGLES, 6, offset) {
	GLSL_Light(light.getX(), light.getY(), light.getWidth(), light.getHeight(), light.getColor(), offset, lightVertices);
}

GLSL_Light::GLSL_Light(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& lightVertices) : GLSL_Object(GL_TRIANGLES, 6, offset) {
	init(x, y, width, height, color, offset, lightVertices);
}

void GLSL_Light::init(float x, float y, float width, float height, Color color, int& offset, std::vector<Vertex>& lightVertices) {
	generateVertices(x, y, width, height, color, lightVertices);
	updateOffset(offset);
}

void GLSL_Light::generateVertices(float x, float y, float width, float height, Color color, std::vector<Vertex>& lightVertices) {
	// top-right corner
	lightVertices.emplace_back(x + width, y + height, 1.0f, 1.0f, color);

	// top-left corner
	lightVertices.emplace_back(x, y + height, -1.0f, 1.0f, color);

	// bottom-left corner
	lightVertices.emplace_back(x, y, -1.0f, -1.0f, color);

	// top-right corner
	lightVertices.emplace_back(x + width, y + height, 1.0f, 1.0f, color);

	// bottom-right corner
	lightVertices.emplace_back(x + width, y, 1.0f, -1.0f, color);

	// bottom-left corner
	lightVertices.emplace_back(x, y, -1.0f, -1.0f, color);
}
