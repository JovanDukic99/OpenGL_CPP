#include "Point.h"

Point::Point(float x, float y, Color color) : GeometryObject(GL_POINTS, 1) {
	init(x, y, color);
}

void Point::init(float x, float y, Color color) {
	generateVertecies(x, y, color);
	uploadVertexData();
}

void Point::generateVertecies(float x, float y, Color color) {
	// one point
	vertexData[0].setPosition(x, y);
	vertexData[0].setColor(color);
}
