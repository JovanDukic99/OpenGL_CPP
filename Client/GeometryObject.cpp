#include "GeometryObject.h"
#include <cstddef>
#include <iostream>

GeometryObject::GeometryObject(GLenum mode, int vertexNumber) : vertexData(new Vertex[vertexNumber]), objectID(0), mode(mode), vertexNumber(vertexNumber)
{
	init();
}

void GeometryObject::init() {
	if (objectID == 0) {
		glGenBuffers(1, &objectID);
	}
}

GLuint GeometryObject::getObjectID(){
	return objectID;
}

void GeometryObject::uploadVertexData() {
	glBindBuffer(GL_ARRAY_BUFFER, objectID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexNumber, vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GeometryObject::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, objectID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	glDrawArrays(mode, 0, vertexNumber);
	glDisableVertexAttribArray(0);
	
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


