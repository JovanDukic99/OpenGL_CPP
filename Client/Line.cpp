#define _USE_MATH_DEFINES
#include "Line.h"
#include <cmath>

Line::Line(float x, float y, float x1, float y1, Color color) : GeometryObject(GL_LINES, 2) {
	init(x, y, x1, y1, color);
}

Line::Line(float x, float y, float x1, float y1, float angle, Color color) : GeometryObject(GL_LINES, 2) {
	init(x, y, x1, y1, angle, color);
}

void Line::init(float x, float y, float x1, float y1, Color color) {
	generateVertecies(x, y, x1, y1, color);
	uploadVertexData();
}

void Line::init(float x, float y, float x1, float y1, float angle, Color color) {
	generateVertecies(x, y, x1, y1, angle, color);
	uploadVertexData();
}

void Line::generateVertecies(float x, float y, float x1, float y1, Color color) {
	//first point
	vertexData[0].setPosition(x, y);
	vertexData[0].setColor(color);

	// second point
	vertexData[1].setPosition(x1, y1);
	vertexData[1].setColor(color);
}

void Line::generateVertecies(float x, float y, float x1, float y1, float angle, Color color) {
	generateVertecies(x, y, x1, y1, color);

	float centerX = x1 * 0.5f;
	float centerY = y1 * 0.5f;

	double radians = (2 * M_PI / 360.0f) * angle;

	for (int i = 0; i < 2; i++) {
		double pX = vertexData[i].position.x;
		double pY = vertexData[i].position.y;
		vertexData[i].position.x = centerX + (pX - centerX) * cos(radians) - (pY - centerY) * sin(radians);
		vertexData[i].position.y = centerY + (pX - centerX) * sin(radians) + (pY - centerY) * cos(radians);
	}
}


