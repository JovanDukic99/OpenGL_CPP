#pragma once
#include <GL/glew.h>
#include "Vertex.h"

class GeometryObject
{
private:
	GLenum mode;
	int vertexNumber;
	int offset;
public:
	GeometryObject(GLenum mode, int vertexNumber, int offset);

	// setters
	void updateOffset(int& offset);

	// getters
	int getOffset();
	int getVertexNumber();
	GLenum getMode();
};

