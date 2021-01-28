#pragma once
#include <GL/glew.h>
#include "Vertex.h"

class ObjectBase
{
private:
	float x;
	float y;
	float widht;
	float height;
	GLuint objectID;


public:
	ObjectBase(float x, float y, float width, float height);
	~ObjectBase();
	void draw();
	void updatePosition(float x, float y);
	float getX();
	float getY();

private:
	void init();
	void updoadVertexData(Vertex* vertexData);
	Vertex* createVertices();
};


