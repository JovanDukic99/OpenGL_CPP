#include "GLSL_Object.h"
#include <cstddef>

GLSL_Object::GLSL_Object(GLenum mode, int vertexNumber, int offset) : mode(mode), vertexNumber(vertexNumber), offset(offset) {

}

void GLSL_Object::updateOffset(int& offset) {
	offset += vertexNumber;
}

// getters
int GLSL_Object::getOffset() const {
	return offset;
}

int GLSL_Object::getVertexNumber() const {
	return vertexNumber;
}

GLenum GLSL_Object::getMode() const {
	return mode;
}





