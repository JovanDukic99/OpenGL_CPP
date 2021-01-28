#include "ObjectBase.h"
#include <cstddef>

ObjectBase::ObjectBase(float x, float y, float width, float height) : x(x), y(y), widht(width), height(height), objectID(0)
{
	init();
}

ObjectBase::~ObjectBase() {
	// delete object ID when object is destroyed
	if (objectID != 0) {
		glDeleteBuffers(1, &objectID);
	}
}

void ObjectBase::init() {
	// generate object ID (vertex buffer object)
	if (objectID == 0) {
		glGenBuffers(1, &objectID);
	}
	updoadVertexData(createVertices());
}

void ObjectBase::updoadVertexData(Vertex* vertexData) {
	glBindBuffer(GL_ARRAY_BUFFER, objectID);

	// send data to binded buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertexData, GL_STREAM_DRAW);
	
	// 0 means no buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex* ObjectBase::createVertices() {
	// create 6 vertices which will defina a square
	Vertex* vertices = new Vertex[6];

	// top-right corner
	vertices[0].position.x = x + widht;
	vertices[0].position.y = y + height;

	// top-left corner
	vertices[1].position.x = x;
	vertices[1].position.y = y + height;

	// bottom-left corner
	vertices[2].position.x = x;
	vertices[2].position.y = y;

	// top-right corner
	vertices[3].position.x = x + widht;
	vertices[3].position.y = y + widht;

	// bottom-left corner
	vertices[4].position.x = x;
	vertices[4].position.y = y;

	// bottom-rigth corner
	vertices[5].position.x = x + widht;
	vertices[5].position.y = y;

	// setting up color
	for (int i = 0; i < 6; i++) {
		vertices[i].color.r = 255;
		vertices[i].color.g = 0;
		vertices[i].color.b = 255;
		vertices[i].color.a = 255; // 255 for a means no transparency
	}

	return vertices;
}

void ObjectBase::draw() {
	// bind buffer object to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, objectID);

	// enable position attribute
	// tell GL what kind of attributes we are giving to him
	// it literally means take first element of VertexArrtibArray
	// and that element is position
	glEnableVertexAttribArray(0);

	// this is the position attribute pointer
	// 0 - index of element in VertexArrtibArray
	// 2 - number of variables (x and y coordinate)
	// type od data in our position array
	// do we want to normalize, convert values to fit range [0; 1.0]
	// size of Vertex struct
	// offset of position struct in Vertex struct
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

	// enable color attribute
	glEnableVertexAttribArray(1);

	// this is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// (what are we drawing, what is first element, number of elements)
	// number of elements <==> number of vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	// unbind buffer when finished, 0 means no buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ObjectBase::updatePosition(float x, float y) {
	this->x = x;
	this->y = y;
}

float ObjectBase::getX() {
	return x;
}

float ObjectBase::getY() {
	return y;
}
