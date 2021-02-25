#define _USE_MATH_DEFINES
#include "GLSL_Circle.h"
#include <cmath>

GLSL_Circle::GLSL_Circle(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices) : GLSL_Object(GL_TRIANGLES, 3 * segments, offset) {
	init(x, y, radius, segments, color, offset, vertices);
}

void GLSL_Circle::init(float x, float y, float radius, int segments, Color color, int& offset, std::vector<Vertex>& vertices) {
	generateVertices(x, y, radius, segments, color, vertices);
	updateOffset(offset);
}

void GLSL_Circle::generateVertices(float x, float y, float radius, int segments, Color color, std::vector<Vertex>& vertices) {
	double increment = (2 * M_PI) / segments;
	double radians = increment;;
	double stepBack = 0.0;

	int index = 0;

	for (int i = 0; i < segments; i++) {
		// origin
		vertices.emplace_back(x, y, color);

		// other two vertices
		vertices.emplace_back((float) (x + (radius * cos(radians))), (float) (y + (radius * sin(radians))), color);
		vertices.emplace_back((float) (x + (radius * cos(stepBack))), (float) (y + (radius * sin(stepBack))), color);

		stepBack = radians;
		radians = radians + increment;
	}
}
