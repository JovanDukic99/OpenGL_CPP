#include "Renderer.h"
#include "Line.h"
#include "Point.h"
#include "Square.h"
#include "Circle.h"
#include <GL/glew.h>
#include <iostream>

Renderer::Renderer() : vertexArrayID(0), vertexBufferID(0), offset(0) {
	init();
}

void Renderer::init() {
	initVertexArray();
}

void Renderer::initVertexArray() {
	glGenVertexArrays(1, &vertexArrayID);
	glGenBuffers(1, &vertexBufferID);

	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);
}

void Renderer::begin() {
	reset();
}

void Renderer::end() {
	uploadVertexData();
	draw();
}

void Renderer::uploadVertexData() {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw() {
	glBindVertexArray(vertexArrayID);
	for (int i = 0; i < geometryObjects.size(); i++) {
		GeometryObject object = geometryObjects[i];
		glDrawArrays(object.getMode(), object.getOffset(), object.getVertexNumber());
	}
	glBindVertexArray(0);
}

// drawing functions
void Renderer::drawSquare(float x, float y, float width, float height, Color color) {
	geometryObjects.emplace_back(Square(x, y, width, height, color, offset, vertices));
}

void Renderer::drawCircle(float x, float y, float radius, int segments, Color color) {
	geometryObjects.emplace_back(Circle(x, y, radius, segments, color, offset, vertices));
}

void Renderer::drawLine(float x, float y, float x1, float y1, Color color) {
	geometryObjects.emplace_back(Line(x, y, x1, y1, color, offset, vertices));
}

void Renderer::drawPoint(float x, float y, Color color) {
	geometryObjects.push_back(Point(x, y, color, offset, vertices));
}

void Renderer::reset() {
	vertices.clear();
	geometryObjects.clear();
	offset = 0;
}

