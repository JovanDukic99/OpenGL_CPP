#include "GLSL_Object.h"
#include <cstddef>

GLSL_Object::GLSL_Object() : mode(0), vertexNumber(0), offset(0) {

}

GLSL_Object::GLSL_Object(GLenum mode, int vertexNumber, int offset) : mode(mode), vertexNumber(vertexNumber), offset(offset) {

}

void GLSL_Object::updateOffset(int& offset) {
	offset += vertexNumber;
}

int GLSL_Object::getOffset() {
	return offset;
}

int GLSL_Object::getVertexNumber() {
	return vertexNumber;
}

GLenum GLSL_Object::getMode() {
	return mode;
}





