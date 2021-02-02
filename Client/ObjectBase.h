#pragma once
#include <GL/glew.h>
#include <string>
#include "Vertex.h"
#include "GLTexture.h"

class ObjectBase
{
private:
	float x;
	float y;
	float width;
	float height;

	GLTexture texture;
	GLuint objectID;

public:
	ObjectBase(float x, float y, float width, float height, std::string textureFilePath);
	~ObjectBase();

	void draw();
	void updatePosition(float x, float y);

	float getX();
	float getY();

private:
	void init(std::string textureFilePath);
	void initObjectID();

	void loadTexture(std::string textureFilePath);
	void updoadVertexData(Vertex* vertexData);

	void drawVertices();
	void bindTexture();
	void unbindTexture();

	Vertex* createVertices();
};


