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
	// constructors
	GLSL_Object(GLenum mode, int vertexNumber, int offset);

	// setters
	void updateOffset(int& offset);
public:
	// getters
	int getOffset() const;
	int getVertexNumber() const;
	GLenum getMode() const;
};

