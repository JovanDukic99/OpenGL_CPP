#pragma once
#include <GL/glew.h>
#include "Vertex.h"

class GeometryObject
{
protected:
	GLuint objectID;
	GLenum mode;
	int vertexNumber;
	Vertex* vertexData;

public:
	GeometryObject(GLenum mode, int vertexNumber);
	GLuint getObjectID();
	void draw();
	void clear();

private:
	void init();

protected:
	void uploadVertexData();
};

