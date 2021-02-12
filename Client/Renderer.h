#pragma once
#include "GeometryObject.h"
#include <vector>

class Renderer
{
private:
	std::vector<GeometryObject> geometryObjects;
	std::vector<Vertex> vertices;
	GLuint vertexArrayID;
	GLuint vertexBufferID;
	int offset;

public:
	Renderer();

	void drawSquare(float x, float y, float width, float height, Color color);
	void drawCircle(float x, float y, float radius, int segments, Color color);
	void drawLine(float x, float y, float x1, float y1, Color color);
	void drawPoint(float x, float y, Color color);

	void begin();
	void end();

private:
	void init();
	void initVertexArray();
	void draw();
	void uploadVertexData();
	void reset();
};


