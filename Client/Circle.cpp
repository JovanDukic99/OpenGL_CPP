#define _USE_MATH_DEFINES
#include "Circle.h"
#include <cmath>

Circle::Circle(float x, float y, float radius, int segments, Color color) : GeometryObject(GL_TRIANGLES, 3 * segments) {
	init(x, y, radius, segments, color);
}

void Circle::init(float x, float y, float radius, int segments, Color color) {
	generateVertices(x, y, radius, segments, color);
	uploadVertexData();
}

void Circle::generateVertices(float x, float y, float radius, int segments, Color color) {
	double increment = (2 * M_PI) / segments;
	double radians = increment;;
	double stepBack = 0.0;

	int index = 0;

	for (int i = 0; i < segments; i++) {
		// origin
		vertexData[index].setPosition(x, y);
		vertexData[index++].setColor(color);

		vertexData[index].position.x = x + (radius * cos(radians));
		vertexData[index].position.y = y + (radius * sin(radians));
		vertexData[index++].setColor(color);

		vertexData[index].position.x = x + (radius * cos(stepBack));
		vertexData[index].position.y = y + (radius * sin(stepBack));
		vertexData[index++].setColor(color);

		stepBack = radians;
		radians = radians + increment;
	}
}
