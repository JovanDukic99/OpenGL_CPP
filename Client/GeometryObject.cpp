#include "GeometryObject.h"
#include <cstddef>
#include <iostream>

GeometryObject::GeometryObject(GLenum mode, int vertexNumber, int offset) : mode(mode), vertexNumber(vertexNumber), offset(offset) {

}

void GeometryObject::updateOffset(int& offset) {
	offset += vertexNumber;
}

int GeometryObject::getOffset() {
	return offset;
}

int GeometryObject::getVertexNumber() {
	return vertexNumber;
}

GLenum GeometryObject::getMode() {
	return mode;
}





