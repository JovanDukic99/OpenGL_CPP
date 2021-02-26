#pragma once
#include <GL/glew.h>
#include "Vertex.h"

class GLSL_Object
{
private:
	GLenum mode;
	int vertexNumber;
	int offset;
protected:
	GLSL_Object();
	GLSL_Object(GLenum mode, int vertexNumber, int offset);

	// setters
	void updateOffset(int& offset);
public:
	// getters
	int getOffset();
	int getVertexNumber();
	GLenum getMode();
};

