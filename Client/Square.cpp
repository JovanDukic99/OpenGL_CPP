#define _USE_MATH_DEFINES
#include "Square.h"
#include <cmath>

Square::Square(float x, float y, float width, float height, Color color) : GeometryObject(GL_TRIANGLES, 6) {
	init(x, y, width, height, color);
}

Square::Square(float x, float y, float width, float height, float angle, Color color) : GeometryObject(GL_TRIANGLES, 6) {
	init(x, y, width, height, angle, color);
}

void Square::init(float x, float y, float width, float height, Color color) {
	generateVertecies(x, y, width, height, color);
	uploadVertexData();
}

void Square::init(float x, float y, float width, float height, float angle, Color color) {
	generateVertecies(x, y, width, height, angle, color);
	uploadVertexData();
}

void Square::generateVertecies(float x, float y, float width, float height, Color color) {
	// top-right corner
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setColor(color);
	
	// top-left corner
	vertexData[1].setPosition(x, y + height);
	vertexData[1].setColor(color);

	// bottom-left corner
	vertexData[2].setPosition(x, y);
	vertexData[2].setColor(color);

	// top-right corner
	vertexData[3].setPosition(x + width, y + height);
	vertexData[3].setColor(color);

	// bottom-right corner
	vertexData[4].setPosition(x + width, y);
	vertexData[4].setColor(color);

	// bottom-left corner
	vertexData[5].setPosition(x, y);
	vertexData[5].setColor(color);
}

void Square::generateVertecies(float x, float y, float width, float height, float angle, Color color) {
	generateVertecies(x, y, width, height, color);

	float centerX = x + (width * 0.5f);
	float centerY = y + (height * 0.5f);

	double radians = (2 * M_PI / 360.0f) * angle;

	for (int i = 0; i < 6; i++) {
		double pX = vertexData[i].position.x;
		double pY = vertexData[i].position.y;
		vertexData[i].position.x = centerX + ((pX - centerX) * cos(radians)) - ((pY - centerY) * sin(radians));
		vertexData[i].position.y = centerY + ((pX - centerX) * sin(radians)) + ((pY - centerY) * cos(radians));
	}
}
