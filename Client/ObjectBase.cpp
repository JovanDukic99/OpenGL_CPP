#include "ObjectBase.h"
#include "ResourceManager.h"
#include <cstddef>

ObjectBase::ObjectBase(float x, float y, float width, float height, std::string textureFilePath) : x(x), y(y), width(width), height(height), objectID(0)
{
	init(textureFilePath);
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::init(std::string textureFilePath)
{
	initObjectID();
	loadTexture(textureFilePath);
	updoadVertexData(createVertices());
}

void ObjectBase::initObjectID()
{
	// generate object ID (vertex buffer object)
	if (objectID == 0)
	{
		glGenBuffers(1, &objectID);
	}
}

void ObjectBase::loadTexture(std::string textureFilePath)
{
	texture = ResourceManager::getTexture(textureFilePath);
}

void ObjectBase::updoadVertexData(Vertex *vertexData)
{
	glBindBuffer(GL_ARRAY_BUFFER, objectID);

	// send data to binded buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertexData, GL_STREAM_DRAW);

	// 0 means no buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex *ObjectBase::createVertices()
{
	// create 6 vertices which will defina a square
	Vertex *vertices = new Vertex[6];

	// top-right corner
	vertices[0].setPosition(x + width, y + height);
	vertices[0].setUV(1.0f, 1.0f);

	// top-left corner
	vertices[1].setPosition(x, y + height);
	vertices[1].setUV(0.0f, 1.0f);

	// bottom-left corner
	vertices[2].setPosition(x, y);
	vertices[2].setUV(0.0f, 0.0f);

	// top-right corner
	vertices[3].setPosition(x + width, y + height);
	vertices[3].setUV(1.0f, 1.0f);

	// bottom-left corner
	vertices[4].setPosition(x, y);
	vertices[4].setUV(0.0f, 0.0f);

	// bottom-rigth corner
	vertices[5].setPosition(x + width, y);
	vertices[5].setUV(1.0f, 0.0f);

	// setting up color
	for (int i = 0; i < 6; i++)
	{
		vertices[i].setColor(255, 0, 255, 255); // 255 for a means no transparency
	}

	return vertices;
}

void ObjectBase::draw()
{
	bindTexture();
	drawVertices();
	unbindTexture();
}

void ObjectBase::drawVertices()
{
	// bind buffer object to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, objectID);

	// enable position attribute
	// tell GL what kind of attributes we are giving to him
	// it literally means take first element of VertexArrtibArray
	// and that element is position
	glEnableVertexAttribArray(0);

	// this is the position attribute pointer
	// 0 - index of element in VertexArrtibArray
	// 2 - number of variables (x and y coordinate)
	// type od data in our position array
	// do we want to normalize, convert values to fit range [0; 1.0]
	// size of Vertex struct
	// offset of position struct in Vertex struct
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

	// enable color attribute
	glEnableVertexAttribArray(1);

	// this is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

	// enable UV attribute
	glEnableVertexAttribArray(2);

	// this is uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

	// (what are we drawing, what is first element, number of elements)
	// number of elements <==> number of vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// unbind buffer when finished, 0 means no buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ObjectBase::bindTexture()
{
	// you can bind more active textures, just increase number
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.ID);
}

void ObjectBase::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ObjectBase::updatePosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

float ObjectBase::getX()
{
	return x;
}

float ObjectBase::getY()
{
	return y;
}
