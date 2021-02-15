#pragma once
#include <GL/glew.h>
#include "Graphics.h"
// struct which contains vertex data
class Vertex {
public:
	Position position;
	Color color;
	UV uv;
public:
	Vertex();
	Vertex(Position position, UV uv, Color color);
	Vertex(float x, float y, Color color);
	Vertex(float x, float y, float u, float v, Color color);

	// setters
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void setColor(Color color);
	void setUV(float u, float v);
	void setUV(UV uv);
	void setPosition(float x, float y);
	void setPosition(Position position);
};