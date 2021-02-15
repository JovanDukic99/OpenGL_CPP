#pragma once
#include <GL/glew.h>
#include "Vertex.h"

class GLSL_Object
{
private:
	GLenum mode;
	int vertexNumber;
	int offset;
public:
	GLSL_Object(GLenum mode, int vertexNumber, int offset);

	// setters
	void updateOffset(int& offset);

	// getters
	int getOffset();
	int getVertexNumber();
	GLenum getMode();
};

