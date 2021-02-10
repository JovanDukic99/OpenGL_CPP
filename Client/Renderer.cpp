#include "Renderer.h"
#include "Line.h"
#include "Point.h"
#include "Square.h"
#include "Circle.h"
#include <GL/glew.h>
#include <iostream>

Renderer::Renderer() {

}

GLuint Renderer::drawLine(float x, float y, float x1, float y1, Color color) {
	// create line
	Line line(x, y, x1, y1, color);

	// add to an array
	objects.push_back(line);

	// return objectID
	return line.getObjectID();
}

GLuint Renderer::drawLine(float x, float y, float x1, float y1, float angle, Color color) {
	// create line
	Line line(x, y, x1, y1, angle, color);

	// add to an array
	objects.push_back(line);

	// return objectID
	return line.getObjectID();
}

GLuint Renderer::drawPoint(float x, float y, Color color) {
	// create point
	Point point(x, y, color);

	// add to an array
	objects.push_back(point);

	// return objectID
	return point.getObjectID();
}

GLuint Renderer::drawSquare(float x, float y, float width, float height, Color color) {
	// create square
	Square square(x, y, width, height, color);

	// add to an array
	objects.push_back(square);

	// return objectID
	return square.getObjectID();
}

GLuint Renderer::drawSquare(float x, float y, float width, float height, float angle, Color color) {
	// create square
	Square square(x, y, width, height, angle ,color);

	// add to an array
	objects.push_back(square);

	// return objectID
	return square.getObjectID();
}

GLuint Renderer::drawCircle(float x, float y, float radius, int segments, Color color) {
	Circle circle(x, y, radius, segments, color);
	objects.push_back(circle);
	return circle.getObjectID();
}

GLuint Renderer::drawLight(float x, float y, float width, float height, Color color) {

	return GLuint();
}


void Renderer::render() {
	for (GeometryObject object : objects) {
		object.draw();
	}
}

void Renderer::clear(){
	for (GeometryObject object : objects) {
		object.clear();
	}
}
